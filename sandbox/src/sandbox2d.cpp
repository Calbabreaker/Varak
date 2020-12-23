#include "sandbox2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

Sandbox2D::Sandbox2D()
{
    VR_PROFILE_FUNCTION();
}

void Sandbox2D::onAttach()
{
    VR_PROFILE_FUNCTION();

    m_vTexture = Varak::Texture2D::create("assets/textures/v.png");
    m_patternTexture = Varak::Texture2D::create("assets/textures/pattern.png");

    Varak::Window& window = Varak::Application::get().getWindow();
    m_editorCamera.setViewportSize(window.getWidth(), window.getHeight());
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

        m_editorCamera.onUpdate(ts);
    }

    // render
    {
        VR_PROFILE_SCOPE("Renderer Prep");

        Varak::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Varak::RenderCommand::clear();
    }

    {
        VR_PROFILE_SCOPE("Renderer Draw");

        static float rotation = 0.0f;
        static float color = 0.0f;
        static float colorIncrease = 0.5f;

        rotation += 90.0f * ts;
        color += colorIncrease * ts;

        if (color > 1.0f)
            colorIncrease = -0.5f;
        else if (color < 0.0f)
            colorIncrease = 0.5f;

        Varak::Renderer2D::resetStats();
        Varak::Renderer2D::beginScene(m_editorCamera.getViewProjection());

        for (uint32_t x = 0; x < 10; x++)
        {
            for (uint32_t y = 0; y < 10; y++)
            {
                Varak::Renderer2D::drawRect({ x + 5.0f, y + 5.0f }, { 0.75f, 0.75f }, m_squareColor);
            }
        }

        Varak::Renderer2D::drawRect({ 2.0f, -0.5f }, { 0.5f, 1.0f }, { 1.0f, 0.0f, 0.0, 1.0f });
        Varak::Renderer2D::drawRect({ 2.0f, 1.0f }, { 0.5f, 0.75f });

        Varak::Renderer2D::drawRotatedRect({ 0.0f, -1.0f }, { 0.75f, 0.75f }, rotation, { 0.0f, color, 1.0f, 1.0f });

        Varak::Renderer2D::drawTexture(m_patternTexture, { 0.0f, 0.0f, -0.5f }, { 10.0f, 10.0f }, 25.0f);
        Varak::Renderer2D::drawTexture(m_vTexture, { 0.0f, 3.0f, 0.25f }, { 3.0f, 3.0f });
        Varak::Renderer2D::drawTexture(m_vTexture, { 2.0f, 3.0f, 0.5f }, { 2.0f, 2.0f }, 1.0f,
                                       { 1.0, 1.0f, 0.0f, 1.0f });

        Varak::Renderer2D::endScene();
    }
}

void Sandbox2D::onImGuiRender()
{
    VR_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = Varak::Renderer2D::getStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.getVertexCount());
    ImGui::Text("Indices: %d", stats.getIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Varak::Event& event)
{
    Varak::EventDispatcher dispatcher(event);
    dispatcher.dispatch<Varak::WindowResizedEvent>(VR_BIND_FUNC(Sandbox2D::onWindowResizedEvent));

    m_editorCamera.onEvent(event);
}

bool Sandbox2D::onWindowResizedEvent(Varak::WindowResizedEvent& event)
{
    m_editorCamera.setViewportSize(event.getWidth(), event.getHeight());
    return false;
}
