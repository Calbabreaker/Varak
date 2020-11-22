#pragma once

#include <varak.h>

class ExampleLayer : public Varak::Layer
{
public:
    ExampleLayer();

    void onUpdate(Varak::Timestep ts) override;
    void onImGuiRender() override;
    void onEvent(Varak::Event& event) override;

private:
    Varak::ShaderLibrary m_shaderLibrary;
    Varak::Ref<Varak::VertexArray> m_squareVA;
    Varak::Ref<Varak::Texture> m_texture;

    Varak::Scope<Varak::CameraController> m_cameraController;

    glm::vec4 m_squareColor1 = { 0.4f, 0.0f, 0.2f, 1.0f };
    glm::vec4 m_squareColor2 = { 0.0f, 0.4f, 0.2f, 1.0f };
};
