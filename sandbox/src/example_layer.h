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
    Varak::Ref<Varak::Shader> m_floatColorShader;
    Varak::Ref<Varak::VertexArray> m_squareVA;

    Varak::Scope<Varak::OrthographicCameraController> m_cameraController;

    glm::vec3 m_squareColor1 = {0.4f, 0.0f, 0.2f};
    glm::vec3 m_squareColor2 = {0.0f, 0.4f, 0.2f};
};
