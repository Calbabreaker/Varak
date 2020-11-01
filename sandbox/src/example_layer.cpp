#include "example_layer.h"

// temporary
#include <glad/glad.h>

ExampleLayer::ExampleLayer()
{
    // clang-format off
    std::array<float, 2*3> positions = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    std::array<uint32_t, 3> indices = {
        0, 1, 2
    };

    // clang-format on

    // vertex array
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    // vertex buffer
    m_vertexBuffer = Varak::VertexBuffer::create(positions.data(), sizeof(positions));
    m_vertexBuffer->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // index buffer
    m_indexBuffer = Varak::IndexBuffer::create(indices.data(), indices.size());
    m_indexBuffer->bind();

    // shader
    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec2 a_position;

        out vec2 v_position;

        void main() 
        {
            v_position = a_position;
            gl_Position = vec4(a_position, 0.0, 1.0);
        }
    )";

    std::string framentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec2 v_position;

        void main() 
        {
            color = vec4(v_position * 0.5 + 0.5, 0.0, 1.0);
        }
    )";

    m_shader = Varak::Shader::create(vertexSrc, framentSrc);
}

void ExampleLayer::onUpdate()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->bind();

    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("test");
    ImGui::Text("hi");
    ImGui::End();
}

void ExampleLayer::onEvent(Varak::Event& event)
{
    Varak::EventDispatcher dispatcher(event);
    dispatcher.dispatch<Varak::KeyPressedEvent>(
        VR_BIND_EVENT_FUNC(ExampleLayer::onKeyPressedEvent));
}

bool ExampleLayer::onKeyPressedEvent(Varak::KeyPressedEvent& event)
{
    VR_TRACE("Key Pressed: {0}", static_cast<char>(event.getKeyCode()));
    return false;
}
