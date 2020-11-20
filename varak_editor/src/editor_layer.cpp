#include "editor_layer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Varak {

    EditorLayer::EditorLayer()
    {
        VR_PROFILE_FUNCTION();

        Window& window = Application::get().getWindow();
        float aspectRatio = static_cast<float>(window.getWidth()) /
                            static_cast<float>(window.getHeight());

        m_cameraController =
            createScope<OrthographicCameraController>(aspectRatio);
    }

    void EditorLayer::onAttach()
    {
        VR_PROFILE_FUNCTION();

        m_vTexture = Texture2D::create("assets/textures/v.png");
        m_patternTexture = Texture2D::create("assets/textures/pattern.png");
    }

    void EditorLayer::onDetach()
    {
        VR_PROFILE_FUNCTION(); //
    }

    void EditorLayer::onUpdate(Timestep ts)
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

            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::clear();
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

            Renderer2D::resetStats();
            Renderer2D::beginScene(m_cameraController->getCamera());

            for (uint32_t x = 0; x < 10; x++)
            {
                for (uint32_t y = 0; y < 10; y++)
                {
                    Renderer2D::drawRect({ x + 5.0f, y + 5.0f },
                                         { 0.75f, 0.75f }, m_squareColor);
                }
            }

            Renderer2D::drawRect({ 2.0f, -0.5f }, { 0.5f, 1.0f },
                                 { 1.0f, 0.0f, 0.0, 1.0f });
            Renderer2D::drawRect({ 2.0f, 1.0f }, { 0.5f, 0.75f });

            Renderer2D::drawRotatedRect({ 0.0f, -1.0f }, { 0.75f, 0.75f },
                                        rotation, { 0.0f, color, 1.0f, 1.0f });

            Renderer2D::drawTexture(m_patternTexture, { 0.0f, 0.0f, -0.5f },
                                    { 10.0f, 10.0f }, 25.0f);
            Renderer2D::drawTexture(m_vTexture, { 0.0f, 3.0f, 0.25f },
                                    { 3.0f, 3.0f });
            Renderer2D::drawTexture(m_vTexture, { 2.0f, 3.0f, 0.5f },
                                    { 2.0f, 2.0f }, 1.0f,
                                    { 1.0, 1.0f, 0.0f, 1.0f });

            Renderer2D::endScene();
        }
    }

    void EditorLayer::onImGuiRender()
    {
        VR_PROFILE_FUNCTION();

        ImGui::Begin("Settings");

        auto stats = Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getVertexCount());
        ImGui::Text("Indices: %d", stats.getIndexCount());

        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
        ImGui::End();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void EditorLayer::onEvent(Event& event)
    {
        m_cameraController->onEvent(event);
    }

} // namespace Varak
