#include "example_layer.h"

ExampleLayer::ExampleLayer()
{
    // clang-format off
    std::array<float, 3*7> positions = {
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
    };

    //std::array<float, 3*7> positions = {
    //     0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    //     1000.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //     500.0f, 1000.0f, 0.0f, 0.0f, 1.0f, 1.0f
    //};

    std::array<uint32_t, 3> indices = {
        0, 1, 2
    };

    Varak::BufferLayout layout = { 
        { Varak::ShaderDataType::Float2, "a_position" }, 
        { Varak::ShaderDataType::Float4, "a_color" } 
    };

    // clang-format on

    // vertex buffer
    Varak::Ref<Varak::VertexBuffer> vertexBuffer =
        Varak::VertexBuffer::create(positions.data(), sizeof(positions));
    vertexBuffer->setLayout(layout);

    // index buffer
    Varak::Ref<Varak::IndexBuffer> indexBuffer =
        Varak::IndexBuffer::create(indices.data(), indices.size());
    indexBuffer->bind();

    // vertex array
    m_vertexArray = Varak::VertexArray::create();
    m_vertexArray->addVertexBuffer(vertexBuffer);
    m_vertexArray->setIndexBuffer(indexBuffer);

    // shader
    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec2 a_position;
        layout(location = 1) in vec4 a_color;

        out vec4 v_color;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        void main() 
        {
            v_color = a_color;
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 0.0, 1.0);
        }
    )";

    std::string framentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec4 v_color;

        void main() 
        {
            color = v_color;
        }
    )";

    m_shader = Varak::Shader::create(vertexSrc, framentSrc);

    // camera
    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) /
                        static_cast<float>(window.getHeight());

    m_cameraController =
        Varak::createScope<Varak::OrthographicCameraController>(aspectRatio);
}

void ExampleLayer::onUpdate()
{
    Varak::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Varak::RenderCommand::clear();

    m_cameraController->onUpdate();

    Varak::Renderer::beginScene(m_cameraController->getCamera());

    Varak::Renderer::submit(m_vertexArray, m_shader);

    Varak::Renderer::endScene();
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("test");
    ImGui::Text("hi");
    ImGui::End();
}

void ExampleLayer::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
