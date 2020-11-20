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

        FrameBufferProperties props;
        props.width = 1280;
        props.height = 720;
        m_frameBuffer = FrameBuffer::create(props);
    }

    void EditorLayer::onDetach()
    {
        VR_PROFILE_FUNCTION(); //
    }

    void EditorLayer::onUpdate(Timestep ts)
    {
        VR_PROFILE_FUNCTION();

        // resize
        FrameBufferProperties props = m_frameBuffer->getProperties();
        if (m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f &&
            (props.width != m_viewportSize.x ||
             props.height != m_viewportSize.y))
        {
            m_frameBuffer->resize(static_cast<uint32_t>(m_viewportSize.x),
                                  static_cast<uint32_t>(m_viewportSize.y));
            m_cameraController->onResize(m_viewportSize.x, m_viewportSize.y);
        }

        // update
        m_cameraController->onUpdate(ts);

        // render
        {
            m_frameBuffer->bind();
            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::clear();
        }

        {
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
            m_frameBuffer->unbind();
        }
    }

    void EditorLayer::onImGuiRender()
    {
        VR_PROFILE_FUNCTION();

        static bool dockSpaceOpen = true;
        static bool fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                            ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockSpaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                    Application::get().close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Stats");

        auto stats = Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getVertexCount());
        ImGui::Text("Indices: %d", stats.getIndexCount());

        ImGui::End(); // Stats

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();
        m_viewportSize = { viewPortPanelSize.x, viewPortPanelSize.y };

        uint64_t rendererID = m_frameBuffer->getColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(rendererID), viewPortPanelSize,
                     ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();

        ImGui::End(); // Dockspace
    }

    void EditorLayer::onEvent(Event& event)
    {
        m_cameraController->onEvent(event);
    }

} // namespace Varak
