#include "example_layer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
{
    // clang-format off
    std::array<float, 4*4> vertices = {
        // Positions, TexCoords
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    std::array<uint32_t, 6> indices = {
        0, 1, 2,
        2, 3, 0
    };

    Varak::BufferLayout layout = { 
        { Varak::ShaderDataType::Float2, "a_position" },
        { Varak::ShaderDataType::Float2, "a_texCoord" }
    };

    // clang-format on

    // vertex buffer
    Varak::Ref<Varak::VertexBuffer> vertexBuffer =
        Varak::VertexBuffer::create(vertices.data(), sizeof(vertices));
    vertexBuffer->setLayout(layout);

    // index buffer
    Varak::Ref<Varak::IndexBuffer> indexBuffer = Varak::IndexBuffer::create(
        indices.data(), static_cast<uint32_t>(indices.size()));
    indexBuffer->bind();

    // vertex array
    m_squareVA = Varak::VertexArray::create();
    m_squareVA->addVertexBuffer(vertexBuffer);
    m_squareVA->setIndexBuffer(indexBuffer);

    // shaders
    std::string flatColorVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec2 a_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() 
            {
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 0.0, 1.0);
            }
        )";

    std::string flatColorFramentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec3 u_color;

            void main() 
            {
                color = vec4(u_color, 1.0);
            }
        )";

    m_flatColorShader =
        Varak::Shader::create(flatColorVertexSrc, flatColorFramentSrc);

    std::string textureVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec2 a_position;
            layout(location = 1) in vec2 a_texCoord;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            out vec2 v_texCoord;

            void main() 
            {
                v_texCoord = a_texCoord;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 0.0, 1.0);
            }
        )";

    std::string textureframentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 v_texCoord;

            uniform sampler2D u_texture;

            void main() 
            {
                color = texture(u_texture, v_texCoord);
            }
        )";

    m_textureShader =
        Varak::Shader::create(textureVertexSrc, textureframentSrc);

    m_texture = Varak::Texture2D::create("assets/textures/v.png");

    // camera
    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) /
                        static_cast<float>(window.getHeight());

    m_cameraController =
        Varak::createScope<Varak::OrthographicCameraController>(aspectRatio);
}

void ExampleLayer::onUpdate(Varak::Timestep ts)
{
    Varak::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Varak::RenderCommand::clear();

    m_cameraController->onUpdate(ts);

    Varak::Renderer::beginScene(m_cameraController->getCamera());

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            m_flatColorShader->setFloat3(
                "u_color", (x + y) % 2 ? m_squareColor1 : m_squareColor2);
            glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), {x, y, 0.0f}) *
                glm::scale(glm::mat4(1.0f), {0.75f, 0.75f, 1.0f});
            Varak::Renderer::submit(m_squareVA, m_flatColorShader, transform);
        }
    }

    m_texture->bind();
    m_textureShader->bind();
    m_textureShader->setInt1("u_texture", 0);
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), {2.0f, 2.0f, 1.0f});
    Varak::Renderer::submit(m_squareVA, m_textureShader, transform);

    Varak::Renderer::endScene();
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color 1", glm::value_ptr(m_squareColor1));
    ImGui::ColorEdit3("Square Color 2", glm::value_ptr(m_squareColor2));
    ImGui::End();
}

void ExampleLayer::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
