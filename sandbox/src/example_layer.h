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

    Varak::Ref<Varak::Shader> m_shader;
    Varak::Ref<Varak::VertexBuffer> m_vertexBuffer;
    Varak::Ref<Varak::IndexBuffer> m_indexBuffer;
};