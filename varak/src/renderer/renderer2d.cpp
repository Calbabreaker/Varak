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

        std::shared_ptr<Shader> textureShader;
        std::shared_ptr<VertexArray> renderVertexArray;
        std::shared_ptr<VertexBuffer> renderVertexBuffer;
        std::shared_ptr<Texture2D> whiteTexture;

        std::vector<QuadVertex> quadVertexBufferArray;
        QuadVertex* quadVertexBufferPtr;
        uint32_t quadIndicesCount;

        std::vector<std::shared_ptr<Texture>> textureSlots;
        uint32_t textureSlotIndex = 1; // 0 = white texture

        std::array<glm::vec4, 4> quadVertexPositions;
        std::array<glm::vec2, 4> quadVertexTexCoords;

        Renderer2D::Statistics stats;
    };

    static Renderer2DData s_data;

    void Renderer2D::init()
    {
        s_data.renderVertexArray = VertexArray::create();

        s_data.renderVertexBuffer =
            VertexBuffer::create(nullptr, sizeof(QuadVertex) * Renderer2DData::maxVertices, false);

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_position" },     //
            { ShaderDataType::Float2, "a_textureCoord" }, //
            { ShaderDataType::Float4, "a_color" },        //
            { ShaderDataType::Float1, "a_textureIndex" }, //
            { ShaderDataType::Float1, "a_tilingFactor" }  //
        };

        s_data.renderVertexBuffer->setLayout(&layout);
        s_data.renderVertexArray->addVertexBuffer(s_data.renderVertexBuffer);

        s_data.quadVertexBufferArray.reserve(Renderer2DData::maxVertices);

        uint16_t* quadIndices = new uint16_t[Renderer2DData::maxIndices];
        for (uint16_t i = 0, offset = 0; i < Renderer2DData::maxIndices; i += 6, offset += 4)
        {
            quadIndices[i + 0] = offset;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;
        }

        std::shared_ptr<IndexBuffer> indexBuffer =
            IndexBuffer::create(quadIndices, Renderer2DData::maxIndices);
        s_data.renderVertexArray->setIndexBuffer(indexBuffer);
        delete[] quadIndices;

        s_data.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data.whiteTexture->setData(&whiteTextureData);

        s_data.textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data.textureShader->bind();

        int maxTextureSlots = RendererAPI::maxTextureSlots;
        s_data.textureSlots.reserve(maxTextureSlots);
        int32_t samplers[maxTextureSlots];
        for (uint32_t i = 0; i < maxTextureSlots; i++)
            samplers[i] = static_cast<int32_t>(i);

        s_data.textureShader->setIntArray("u_textures", samplers, maxTextureSlots);

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
        // set to nullptr to lower refcount and destroy
        s_data.textureShader = nullptr;
        s_data.renderVertexBuffer = nullptr;
        s_data.renderVertexArray = nullptr;
        s_data.whiteTexture = nullptr;
    }

    void Renderer2D::beginScene(const glm::mat4& viewProj)
    {
        s_data.textureShader->bind();
        s_data.textureShader->setMat4("u_viewProjection", viewProj);

        startBatch();
    }

    void Renderer2D::endScene() { flush(); }

    void Renderer2D::startBatch()
    {
        s_data.quadIndicesCount = 0;
        s_data.quadVertexBufferPtr = s_data.quadVertexBufferArray.data();
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

        QuadVertex* arrayPtr = s_data.quadVertexBufferArray.data();
        uint32_t size =
            static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_data.quadVertexBufferPtr) -
                                  reinterpret_cast<uint8_t*>(arrayPtr));
        s_data.renderVertexBuffer->setSubData(arrayPtr, size);

        // bind textures
        for (uint32_t i = 0; i < s_data.textureSlotIndex; i++)
            s_data.textureSlots[i]->bind(i);

        RenderCommand::drawIndexed(s_data.renderVertexArray, s_data.quadIndicesCount);

        s_data.stats.drawCalls++;
    }

    void Renderer2D::drawRect(const glm::mat4& transform, const glm::vec4& color)
    {
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

    void Renderer2D::drawTexture(const std::shared_ptr<Texture>& texture,
                                 const glm::mat4& transform, float tilingFactor,
                                 const glm::vec4& tint)
    {
        if (s_data.quadIndicesCount >= Renderer2DData::maxIndices)
            nextBatch();

        // find texture slot
        uint8_t textureIndex = 0;
        for (uint8_t i = 1; i < s_data.textureSlotIndex; i++)
        {
            if (*texture == *s_data.textureSlots[i])
            {
                textureIndex = i;
                break;
            }
        }

        // if not found then put into array
        if (textureIndex == 0)
        {
            if (s_data.textureSlotIndex >= s_data.textureSlots.capacity())
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
            s_data.quadVertexBufferPtr->texIndex = static_cast<float>(textureIndex);
            s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;

            s_data.quadVertexBufferPtr++;
        }

        s_data.quadIndicesCount += 6;

        s_data.stats.quadCount++;
    }

    void Renderer2D::resetStats()
    {
        memset(&s_data.stats, 0, sizeof(Statistics)); //
    }

    const Renderer2D::Statistics& Renderer2D::getStats()
    {
        return s_data.stats; //
    }

} // namespace Varak
