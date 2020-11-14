#include "varak/renderer/renderer2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Varak {

    struct Renderer2DData
    {
        Ref<Shader> flatColorShader;
        Ref<VertexArray> quadVertexArray;
    };

    Renderer2DData* s_data;

    void Renderer2D::init()
    {
        s_data = new Renderer2DData(); //

        s_data->quadVertexArray = Varak::VertexArray::create();

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
        indexBuffer->bind();

        s_data->quadVertexArray = VertexArray::create();
        s_data->quadVertexArray->addVertexBuffer(vertexBuffer);
        s_data->quadVertexArray->setIndexBuffer(indexBuffer);

        s_data->flatColorShader =
            Shader::create("assets/shaders/flat_color.glsl");
    }

    void Renderer2D::shutdown()
    {
        delete s_data; //
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        s_data->flatColorShader->bind();
        s_data->flatColorShader->setMat4("u_viewProjection",
                                         camera.getViewProjection());
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size,
                              const glm::vec4& color)
    {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size,
                              const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        drawQuad(transform, color);
    }

    void Renderer2D::drawQuad(const glm::mat4& transform,
                              const glm::vec4& color)
    {
        s_data->quadVertexArray->bind();
        s_data->flatColorShader->bind();
        s_data->flatColorShader->setFloat4("u_color", color);
        s_data->flatColorShader->setMat4("u_transform", transform);
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

} // namespace Varak
