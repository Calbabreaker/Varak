#include "varak/renderer/renderer2d.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    struct Renderer2DData
    {
        Ref<Shader> textureShader;
        Ref<VertexArray> quadVertexArray;
        Ref<Texture2D> whiteTexture;
    };

    static Renderer2DData s_data;

    void Renderer2D::init()
    {
        VR_PROFILE_FUNCTION();

        std::array<float, 4 * 4> vertices = {
            // Positions, TexCoords
            -0.5f, -0.5f, 0.0f, 0.0f, //
            0.5f,  -0.5f, 1.0f, 0.0f, //
            0.5f,  0.5f,  1.0f, 1.0f, //
            -0.5f, 0.5f,  0.0f, 1.0f  //
        };

        Ref<VertexBuffer> vertexBuffer =
            VertexBuffer::create(vertices.data(), sizeof(vertices));
        vertexBuffer->setLayout({{ShaderDataType::Float2, "a_position"},
                                 {ShaderDataType::Float2, "a_texCoord"}});

        std::array<uint32_t, 6> indices = {0, 1, 2, 2, 3, 0};
        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(
            indices.data(), static_cast<uint32_t>(indices.size()));

        s_data.quadVertexArray = VertexArray::create();
        s_data.quadVertexArray->addVertexBuffer(vertexBuffer);
        s_data.quadVertexArray->setIndexBuffer(indexBuffer);

        s_data.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        s_data.textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data.textureShader->bind();
        s_data.textureShader->setInt1("u_texture", 0);
    }

    void Renderer2D::shutdown()
    {
        VR_PROFILE_FUNCTION(); //
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        VR_PROFILE_FUNCTION();

        s_data.textureShader->bind();
        s_data.textureShader->setMat4("u_viewProjection",
                                      camera.getViewProjection());
    }

    void Renderer2D::endScene()
    {
        VR_PROFILE_FUNCTION(); //
    }

    void Renderer2D::drawRect(const glm::vec2& position, const glm::vec2& size,
                              const glm::vec4& color)
    {
        drawRect({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawRect(const glm::vec3& position, const glm::vec2& size,
                              const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) *
            glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        drawRect(transform, color);
    }

    void Renderer2D::drawRotatedRect(const glm::vec3& position,
                                     const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation),
                        {0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        drawRect(transform, color);
    }

    void Renderer2D::drawRotatedRect(const glm::vec2& position,
                                     const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        drawRotatedRect({position.x, position.y, 0.0f}, size, rotation, color);
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture,
                                 const glm::vec2& position,
                                 const glm::vec2& size, float tilingFactor,
                                 const glm::vec4& tint)
    {
        drawTexture(texture, {position.x, position.y, 0.0f}, size, tilingFactor,
                    tint);
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture,
                                 const glm::vec3& position,
                                 const glm::vec2& size, float tilingFactor,
                                 const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) *
            glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        drawTexture(texture, transform, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedTexture(const Ref<Texture>& texture,
                                        const glm::vec2& position,
                                        const glm::vec2& size, float rotation,
                                        float tilingFactor,
                                        const glm::vec4& tint)
    {
        drawRotatedTexture(texture, {position.x, position.y, 0.0f}, size,
                           rotation, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedTexture(const Ref<Texture>& texture,
                                        const glm::vec3& position,
                                        const glm::vec2& size, float rotation,
                                        float tilingFactor,
                                        const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation),
                        {0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        drawTexture(texture, transform, tilingFactor, tint);
    }

    void Renderer2D::drawRect(const glm::mat4& transform,
                              const glm::vec4& color)
    {
        VR_PROFILE_FUNCTION();

        s_data.textureShader->setFloat4("u_color", color);
        s_data.whiteTexture->bind();

        s_data.textureShader->setMat4("u_transform", transform);
        s_data.quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data.quadVertexArray);
    }

    void Renderer2D::drawTexture(const Ref<Texture>& texture,
                                 const glm::mat4& transform, float tilingFactor,
                                 const glm::vec4& tint)
    {
        VR_PROFILE_FUNCTION();

        s_data.textureShader->setFloat4("u_color", tint);
        s_data.textureShader->setFloat1("u_tilingFactor", tilingFactor);
        texture->bind();

        s_data.textureShader->setMat4("u_transform", transform);
        s_data.quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data.quadVertexArray);
    }

} // namespace Varak
