#include "sandbox2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
{
    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) /
                        static_cast<float>(window.getHeight());

    m_cameraController =
        Varak::createScope<Varak::OrthographicCameraController>(aspectRatio);
}

void Sandbox2D::onAttach()
{
    m_squareVA = Varak::VertexArray::create();

    std::array<float, 4 * 4> vertices = {
        // Positions, TexCoords
        -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f,  -0.5f, 1.0f, 0.0f, //
        0.5f,  0.5f,  1.0f, 1.0f, //
        -0.5f, 0.5f,  0.0f, 1.0f  //
    };

    Varak::Ref<Varak::VertexBuffer> vertexBuffer =
        Varak::VertexBuffer::create(vertices.data(), sizeof(vertices));
    vertexBuffer->setLayout({{Varak::ShaderDataType::Float2, "a_position"},
                             {Varak::ShaderDataType::Float2, "a_texCoord"}});

    std::array<uint32_t, 6> indices = {0, 1, 2, 2, 3, 0};
    Varak::Ref<Varak::IndexBuffer> indexBuffer = Varak::IndexBuffer::create(
        indices.data(), static_cast<uint32_t>(indices.size()));
    indexBuffer->bind();

    m_squareVA = Varak::VertexArray::create();
    m_squareVA->addVertexBuffer(vertexBuffer);
    m_squareVA->setIndexBuffer(indexBuffer);

    m_flatColorShader = Varak::Shader::create("assets/shaders/flat_color.glsl");

    m_texture = Varak::Texture2D::create("assets/textures/v.png");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Varak::Timestep ts)
{
    // update
    m_cameraController->onUpdate(ts);

    // render
    Varak::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Varak::RenderCommand::clear();

    Varak::Renderer::beginScene(m_cameraController->getCamera());

    m_flatColorShader->bind();
    m_flatColorShader->setFloat4("u_color", m_squareColor);

    Varak::Renderer::submit(m_squareVA, m_flatColorShader,
                            glm::scale(glm::mat4(1.0f), {2.0f, 2.0f, 1.0f}));

    Varak::Renderer::endScene();
}

void Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
