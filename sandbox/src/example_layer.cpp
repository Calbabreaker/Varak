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
    Varak::Ref<Varak::VertexBuffer> vertexBuffer = Varak::VertexBuffer::create(vertices.data(), sizeof(vertices));
    vertexBuffer->setLayout(layout);

    // index buffer
    Varak::Ref<Varak::IndexBuffer> indexBuffer =
        Varak::IndexBuffer::create(indices.data(), static_cast<uint32_t>(indices.size()));
    indexBuffer->bind();

    // vertex array
    m_squareVA = Varak::VertexArray::create();
    m_squareVA->addVertexBuffer(vertexBuffer);
    m_squareVA->setIndexBuffer(indexBuffer);

    // shaders
    m_shaderLibrary.add(Varak::Shader::create("test", "void main() {}", "void main() {}"));
    m_shaderLibrary.load("assets/shaders/flat_color.glsl");
    m_shaderLibrary.load("assets/shaders/texture.glsl");

    // textures
    m_texture = Varak::Texture2D::create("assets/textures/v.png");

    // camera
    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());

    m_cameraController = Varak::createScope<Varak::CameraController>(aspectRatio);
}

void ExampleLayer::onUpdate(Varak::Timestep ts)
{
    Varak::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Varak::RenderCommand::clear();

    m_cameraController->onUpdate(ts);

    Varak::Renderer::beginScene(m_cameraController->getCamera(), m_cameraController->getTransform());

    auto flatColorShader = m_shaderLibrary.get("flat_color");

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            flatColorShader->setFloat4("u_color", (x + y) % 2 ? m_squareColor1 : m_squareColor2);
            glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), { x, y, 0.0f }) * glm::scale(glm::mat4(1.0f), { 0.75f, 0.75f, 1.0f });
            Varak::Renderer::submit(m_squareVA, flatColorShader, transform);
        }
    }

    auto textureShader = m_shaderLibrary.get("texture");
    m_texture->bind();
    textureShader->bind();
    textureShader->setInt1("u_texture", 0);
    textureShader->setFloat4("u_color", glm::vec4(1.0f));
    textureShader->setFloat1("u_tilingFactor", 1.0f);
    Varak::Renderer::submit(m_squareVA, textureShader,
                            glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f }) *
                                glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.5f }));

    Varak::Renderer::endScene();
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color 1", glm::value_ptr(m_squareColor1));
    ImGui::ColorEdit4("Square Color 2", glm::value_ptr(m_squareColor2));
    ImGui::End();
}

void ExampleLayer::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
