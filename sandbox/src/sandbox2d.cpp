#include "sandbox2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
{
    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) /
                        static_cast<float>(window.getHeight());

    m_cameraController =
        Varak::createScope<Varak::OrthographicCameraController>(aspectRatio);
}

void Sandbox2D::onAttach()
{
    m_texture = Varak::Texture2D::create("assets/textures/v.png");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Varak::Timestep ts)
{
    // update
    m_cameraController->onUpdate(ts);

    // render
    Varak::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Varak::RenderCommand::clear();

    Varak::Renderer2D::beginScene(m_cameraController->getCamera());

    Varak::Renderer2D::drawQuad({0.0f, 0.0f}, {2.0f, 2.0f}, m_squareColor);
    Varak::Renderer2D::drawQuad({2.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});

    Varak::Renderer2D::endScene();
}

void Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
