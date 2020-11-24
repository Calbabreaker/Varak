#include "vrpch.h"

#include "editor_layer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

namespace Varak {

    void EditorLayer::onAttach()
    {
        VR_PROFILE_FUNCTION();

        m_vTexture = Texture2D::create("assets/textures/v.png");
        m_patternTexture = Texture2D::create("assets/textures/pattern.png");

        Window& window = Application::get().getWindow();
        uint32_t width = window.getWidth();
        uint32_t height = window.getHeight();

        m_cameraController = createScope<CameraController>(width, height);

        FrameBufferProperties props;
        props.width = width;
        props.height = height;
        m_frameBuffer = FrameBuffer::create(props);

        m_scene = createRef<Scene>(width, height);
        m_squareEntity = m_scene->createEntity();

        m_squareEntity.addComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        m_cameraEntity = m_scene->createEntity("Camera");
        CameraComponent& camera = m_cameraEntity.addComponent<CameraComponent>();

        VR_CORE_TRACE(m_cameraEntity.getComponent<IdentifierComponent>().name);
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
            (props.width != m_viewportSize.x || props.height != m_viewportSize.y))
        {
            uint32_t width = static_cast<uint32_t>(m_viewportSize.x);
            uint32_t height = static_cast<uint32_t>(m_viewportSize.y);

            m_frameBuffer->resize(width, height);
            m_cameraController->onResize(width, height);
            m_scene->onViewportResize(width, height);
        }

        // update
        if (m_viewportFocused)
            m_cameraController->onUpdate(ts);

        // render
        m_frameBuffer->bind();
        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::clear();

        Renderer2D::resetStats();

        // camera controller will be back after add play button
        m_scene->onUpdate(ts);

        m_frameBuffer->unbind();
    }

    void EditorLayer::onImGuiRender()
    {
        VR_PROFILE_FUNCTION();

        static bool dockSpaceOpen = true;
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockSpaceOpen, windowFlags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
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

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        m_viewportFocused = ImGui::IsWindowFocused();
        m_viewportHovered = ImGui::IsWindowHovered();
        Application::get().getImGuiLayer()->blockEvents(!m_viewportHovered || !m_viewportFocused);

        ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();
        m_viewportSize = { viewPortPanelSize.x, viewPortPanelSize.y };

        uint64_t rendererID = m_frameBuffer->getColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(rendererID), viewPortPanelSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();

        ImGui::End(); // Dockspace
    }

    void EditorLayer::onEvent(Event& event)
    {
        m_cameraController->onEvent(event); //
    }

} // namespace Varak
