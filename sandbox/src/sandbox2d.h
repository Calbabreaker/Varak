#pragma once

#include <varak.h>

class Sandbox2D : public Varak::Layer
{
public:
    Sandbox2D();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(Varak::Timestep ts) override;
    void onImGuiRender() override;
    void onEvent(Varak::Event& event) override;

private:
    Varak::Ref<Varak::Texture> m_texture;

    Varak::Scope<Varak::OrthographicCameraController> m_cameraController;

    glm::vec4 m_squareColor = {0.0f, 0.4f, 0.2f, 1.0f};
};