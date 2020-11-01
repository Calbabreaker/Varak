#pragma once

#include <varak.h>

class ExampleLayer : public Varak::Layer
{
public:
    ExampleLayer();

    void onUpdate() override;
    void onImGuiRender() override;
    void onEvent(Varak::Event& event) override;
    bool onKeyPressedEvent(Varak::KeyPressedEvent& event);

private:
    uint32_t m_vertexArray;

    std::shared_ptr<Varak::Shader> m_shader;
    std::shared_ptr<Varak::VertexBuffer> m_vertexBuffer;
    std::shared_ptr<Varak::IndexBuffer> m_indexBuffer;
};