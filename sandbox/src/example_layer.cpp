#include "example_layer.h"

// temporary
#include <glad/glad.h>

using namespace Varak;

namespace {

    GLenum shaderTypeOpenGL(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float1: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int1: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
        }

        VR_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

} // namespace

ExampleLayer::ExampleLayer()
{
    // clang-format off
    std::array<float, 3*7> positions = {
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
    };

    std::array<uint32_t, 3> indices = {
        0, 1, 2
    };

    BufferLayout layout = { 
        { ShaderDataType::Float2, "a_position" }, 
        { ShaderDataType::Float4, "a_color" } 
    };

    // clang-format on

    // vertex array
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    // vertex buffer
    m_vertexBuffer = VertexBuffer::create(positions.data(), sizeof(positions));
    m_vertexBuffer->bind();
    m_vertexBuffer->setLayout(layout);

    uint32_t index = 0;
    for (auto& element : m_vertexBuffer->getLayout())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.getComponentCount(),
                              shaderTypeOpenGL(element.type),
                              element.normalized, layout.getStride(),
                              reinterpret_cast<const void*>(element.offset));
        index++;
    }

    // index buffer
    m_indexBuffer = IndexBuffer::create(indices.data(), indices.size());
    m_indexBuffer->bind();

    // shader
    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec2 a_position;
        layout(location = 1) in vec4 a_color;

        out vec4 v_color;

        void main() 
        {
            v_color = a_color;
            gl_Position = vec4(a_position, 0.0, 1.0);
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

    m_shader = Shader::create(vertexSrc, framentSrc);
}

void ExampleLayer::onUpdate()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->bind();

    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT,
                   nullptr);
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("test");
    ImGui::Text("hi");
    ImGui::End();
}

void ExampleLayer::onEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyPressedEvent>(
        VR_BIND_EVENT_FUNC(ExampleLayer::onKeyPressedEvent));
}

bool ExampleLayer::onKeyPressedEvent(KeyPressedEvent& event)
{
    VR_TRACE("Key Pressed: {0}", static_cast<char>(event.getKeyCode()));
    return false;
}
