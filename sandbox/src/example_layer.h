#pragma once

#include <varak.h>

class ExampleLayer : public Varak::Layer
{
public:
    ExampleLayer();

    void onUpdate() override;
    void onImGuiRender() override;
    void onEvent(Varak::Event& event) override;

private:
    Varak::Ref<Varak::Shader> m_shader;
    Varak::Ref<Varak::VertexArray> m_vertexArray;

    Varak::Scope<Varak::OrthographicCameraController> m_cameraController;
};