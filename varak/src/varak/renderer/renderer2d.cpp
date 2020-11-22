#include "varak/renderer/renderer2d.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec4 color;
        float texIndex;
        float tilingFactor;
    };

    struct Renderer2DData
    {
        // per draw call
        static const uint32_t maxQuads = 10000;
        static const uint32_t maxVertices = maxQuads * 4;
        static const uint32_t maxIndices = maxQuads * 6;
        // TODO: figure out max for device
        static const uint32_t maxTextureSlots = 32;

        Ref<Shader> textureShader;
        Ref<VertexArray> quadVertexArray;
        Ref<VertexBuffer> quadVertexBufer;
        Ref<Texture2D> whiteTexture;

        QuadVertex* quadVertexBufferBase;
        QuadVertex* quadVertexBufferPtr;
        uint32_t quadIndicesCount;

        std::array<Ref<Texture>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 1; // 0 = white texture

        std::array<glm::vec4, 4> quadVertexPositions;
        std::array<glm::vec2, 4> quadVertexTexCoords;

        Renderer2D::Statistics stats;
    };

    static Renderer2DData s_data;

    void Renderer2D::init()
    {
        VR_PROFILE_FUNCTION();

        s_data.quadVertexArray = VertexArray::create();

        s_data.quadVertexBufer = VertexBuffer::create(sizeof(QuadVertex) * Renderer2DData::maxVertices);

        s_data.quadVertexBufer->setLayout({
            { ShaderDataType::Float3, "a_position" },    //
            { ShaderDataType::Float2, "a_texCoord" },    //
            { ShaderDataType::Float4, "a_color" },       //
            { ShaderDataType::Float1, "a_texIndex" },    //
            { ShaderDataType::Float1, "a_tilingFactor" } //
        });
        s_data.quadVertexArray->addVertexBuffer(s_data.quadVertexBufer);

        s_data.quadVertexBufferBase = new QuadVertex[Renderer2DData::maxVertices];

        uint32_t* quadIndices = new uint32_t[Renderer2DData::maxIndices];
        uint32_t offset = 0;

        for (uint32_t i = 0; i < Renderer2DData::maxIndices; i += 6)
        {
            quadIndices[i + 0] = offset;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(quadIndices, Renderer2DData::maxIndices);
        s_data.quadVertexArray->setIndexBuffer(indexBuffer);
        delete[] quadIndices;

        s_data.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        s_data.textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data.textureShader->bind();

        int32_t samplers[s_data.maxTextureSlots];
        for (uint32_t i = 0; i < s_data.maxTextureSlots; i++)
            samplers[i] = i;

        s_data.textureShader->setIntArray("u_textures", samplers, s_data.maxTextureSlots);

        // white texture
        s_data.textureSlots[0] = s_data.whiteTexture;

        s_data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        s_data.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
        s_data.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

        s_data.quadVertexTexCoords[0] = { 0.0f, 0.0f };
        s_data.quadVertexTexCoords[1] = { 1.0f, 0.0f };
        s_data.quadVertexTexCoords[2] = { 1.0f, 1.0f };
        s_data.quadVertexTexCoords[3] = { 0.0f, 1.0f };
    }

    void Renderer2D::shutdown()
    {
        VR_PROFILE_FUNCTION();

        delete[] s_data.quadVertexBufferBase;
    }

    void Renderer2D::beginScene(const Camera& camera, const glm::mat4& transform)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 viewProj = camera.getProjection() * glm::inverse(transform);

        s_data.textureShader->bind();
        s_data.textureShader->setMat4("u_viewProjection", viewProj);

        startBatch();
    }

    void Renderer2D::endScene()
    {
        VR_PROFILE_FUNCTION();

        flush();
    }

    void Renderer2D::startBatch()
    {
        s_data.quadIndicesCount = 0;
        s_data.quadVertexBufferPtr = s_data.quadVertexBufferBase;
        s_data.textureSlotIndex = 1;
    }

    void Renderer2D::nextBatch()
    {
        flush();
        startBatch();
    }

    void Renderer2D::flush()
    {
        if (s_data.quadIndicesCount == 0)
            return;

        uint32_t size = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_data.quadVertexBufferPtr) -
                                              reinterpret_cast<uint8_t*>(s_data.quadVertexBufferBase));

        s_data.quadVertexBufer->setData(s_data.quadVertexBufferBase, size);

        // bind textures
        for (uint32_t i = 0; i < s_data.textureSlotIndex; i++)
            s_data.textureSlots[i]->bind(i);

        RenderCommand::drawIndexed(s_data.quadVertexArray, s_data.quadIndicesCount);

        s_data.stats.drawCalls++;
    }

    void Renderer2D::drawRect(const glm::mat4& transform, const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        if (s_data.quadIndicesCount >= Renderer2DData::maxIndices)
            nextBatch();

        for (uint8_t i = 0; i < s_data.quadVertexPositions.size(); i++)
        {
            s_data.quadVertexBufferPtr->position = transform * s_data.quadVertexPositions[i];
            s_data.quadVertexBufferPtr->color = color;
            s_data.quadVertexBufferPtr->texCoord = s_data.quadVertexTexCoords[i];
            s_data.quadVertexBufferPtr->texIndex = 0.0f; // white texture
            s_data.quadVertexBufferPtr->tilingFactor = 1.0f;

            s_data.quadVertexBufferPtr++;
        }

        s_data.quadIndicesCount += 6;

        s_data.stats.quadCount++;
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture, const glm::mat4& transform, float tilingFactor,
                                 const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        if (s_data.quadIndicesCount >= Renderer2DData::maxIndices)
            nextBatch();

        // find texture slot
        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_data.textureSlotIndex; i++)
        {
            if (*texture == *s_data.textureSlots[i])
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        // if not found then put into array
        if (textureIndex == 0.0f)
        {
            if (s_data.textureSlotIndex >= Renderer2DData::maxTextureSlots)
                nextBatch();

            textureIndex = static_cast<float>(s_data.textureSlotIndex);
            s_data.textureSlots[s_data.textureSlotIndex] = texture;
            s_data.textureSlotIndex++;
        }

        for (uint8_t i = 0; i < s_data.quadVertexPositions.size(); i++)
        {
            s_data.quadVertexBufferPtr->position = transform * s_data.quadVertexPositions[i];
            s_data.quadVertexBufferPtr->color = tint;
            s_data.quadVertexBufferPtr->texCoord = s_data.quadVertexTexCoords[i];
            s_data.quadVertexBufferPtr->texIndex = textureIndex;
            s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;

            s_data.quadVertexBufferPtr++;
        }

        s_data.quadIndicesCount += 6;

        s_data.stats.quadCount++;
    }

    void Renderer2D::drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        drawRect({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::drawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawRect(transform, color);
    }

    void Renderer2D::drawRotatedRect(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        drawRotatedRect({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::drawRotatedRect(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawRect(transform, color);
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture, const glm::vec2& position, const glm::vec2& size,
                                 float tilingFactor, const glm::vec4& tint)
    {
        drawTexture(texture, { position.x, position.y, 0.0f }, size, tilingFactor, tint);
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture, const glm::vec3& position, const glm::vec2& size,
                                 float tilingFactor, const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawTexture(texture, transform, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedTexture(const Ref<Texture>& texture, const glm::vec2& position, const glm::vec2& size,
                                        float rotation, float tilingFactor, const glm::vec4& tint)
    {
        drawRotatedTexture(texture, { position.x, position.y, 0.0f }, size, rotation, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedTexture(const Ref<Texture>& texture, const glm::vec3& position, const glm::vec2& size,
                                        float rotation, float tilingFactor, const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        drawTexture(texture, transform, tilingFactor, tint);
    }

    void Renderer2D::resetStats()
    {
        memset(&s_data.stats, 0, sizeof(Statistics)); //
    }

    Renderer2D::Statistics Renderer2D::getStats()
    {
        return s_data.stats; //
    }

} // namespace Varak
