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
    uint32_t m_vertexArray, m_vertexBuffer, m_indexBuffer;
};