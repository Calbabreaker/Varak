#include "sandbox2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
{
    VR_PROFILE_FUNCTION();

    Varak::Window& window = Varak::Application::get().getWindow();
    float aspectRatio = static_cast<float>(window.getWidth()) /
                        static_cast<float>(window.getHeight());

    m_cameraController =
        Varak::createScope<Varak::OrthographicCameraController>(aspectRatio);
}

void Sandbox2D::onAttach()
{
    VR_PROFILE_FUNCTION();

    m_vTexture = Varak::Texture2D::create("assets/textures/v.png");
    m_patternTexture = Varak::Texture2D::create("assets/textures/pattern.png");
}

void Sandbox2D::onDetach()
{
    VR_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(Varak::Timestep ts)
{
    VR_PROFILE_FUNCTION();

    // update
    {
        VR_PROFILE_SCOPE("Update");

        m_cameraController->onUpdate(ts);
    }

    // render
    {
        VR_PROFILE_SCOPE("Renderer Prep");

        Varak::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Varak::RenderCommand::clear();
    }

    {
        VR_PROFILE_SCOPE("Renderer Draw");

        static float rotation = 0.0f;
        static float color = 0.0f;
        static float colorIncrease = 0.5f;

        rotation += 45.0f * ts;
        color += colorIncrease * ts;

        if (color > 1.0f)
            colorIncrease = -0.5f;
        else if (color < 0.0f)
            colorIncrease = 0.5f;

        Varak::Renderer2D::beginScene(m_cameraController->getCamera());

        Varak::Renderer2D::drawRect({0.0f, 0.0f}, {1.0f, 1.0f}, m_squareColor);
        Varak::Renderer2D::drawRect({2.0f, -0.5f}, {0.5f, 1.0f},
                                    {1.0f, 0.0f, 0.0, 1.0f});
        Varak::Renderer2D::drawRect({2.0f, 1.0f}, {0.5f, 0.75f});

        Varak::Renderer2D::drawRotatedRect({0.0f, -1.0f}, {0.75f, 0.75f},
                                           rotation,
                                           {0.0f, color, 1.0f, 1.0f});

        Varak::Renderer2D::drawTexture(m_patternTexture, {0.0f, 0.0f, -0.5f},
                                       {10.0f, 10.0f}, 25.0f);
        Varak::Renderer2D::drawTexture(m_vTexture, {0.0f, 3.0f, 0.25f},
                                       {3.0f, 3.0f});
        Varak::Renderer2D::drawTexture(m_vTexture, {2.0f, 3.0f, 0.5f},
                                       {2.0f, 2.0f}, 1.0f,
                                       {1.0, 1.0f, 0.0f, 1.0f});

        Varak::Renderer2D::endScene();
    }
}

void Sandbox2D::onImGuiRender()
{
    VR_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Varak::Event& event)
{
    m_cameraController->onEvent(event);
}
