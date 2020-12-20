#include "vrpch.h"

#include "editor_layer.h"
#include "varak/imgui/imgui_helper.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

#include <fontawesome/fontawesome_icons.h>

#include <imgui.h>

namespace Varak {

    EditorLayer::EditorLayer() : m_sceneHierarchyPanel(&m_inspectorPanel) {}

    void EditorLayer::onAttach()
    {
        VR_PROFILE_FUNCTION();

        Window& window = Application::get().getWindow();
        uint32_t width = window.getWidth();
        uint32_t height = window.getHeight();

        m_editorCamera.setViewportSize(width, height);

        FrameBufferProperties props;
        props.width = width;
        props.height = height;
        m_frameBuffer = FrameBuffer::create(props);

        m_scene = createRef<Scene>(width, height);
        m_sceneHierarchyPanel.setScene(m_scene);

        m_squareEntity = m_scene->createEntity();
        m_squareEntity.addComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        m_cameraEntity = m_scene->createEntity("Camera");
        m_cameraEntity.addComponent<CameraComponent>();
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
            m_editorCamera.setViewportSize(width, height);
            m_scene->onViewportResize(width, height);
        }

        // update
        if (m_viewportFocused)
            m_editorCamera.onUpdate(ts);

        // render
        m_frameBuffer->bind();
        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::clear();

        Renderer2D::resetStats();

        if (m_isPlaying)
            m_scene->onUpdateRuntime(ts);
        else
            m_scene->onUpdateEditor(ts, m_editorCamera);

        m_frameBuffer->unbind();
    }

    void EditorLayer::onImGuiRender()
    {
        VR_PROFILE_FUNCTION();

        static bool dockSpaceOpen = true;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

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
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(300.0f, 50.0f));
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        }

        ImGui::PopStyleVar();

        // Menu Bar
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f)); // for menubar
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        if (ImGui::BeginMainMenuBar())
        {
            // Dropdowns
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                    Application::get().close();

                ImGui::EndMenu();
            }

            // Play, pause, stop scene
            ImGuiHelper::pushDisabled(m_isPlaying);
            ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 2.0f - ImGui::CalcTextSize(ICON_FA_PLAY).x * 2.0f);
            if (ImGuiHelper::drawClickableText("##play", ICON_FA_PLAY))
            {
                m_isPlaying = true;
                m_scene->onPlayRuntime();
                ImGuiHelper::pushDisabled();
            }
            ImGuiHelper::popDisabled(m_isPlaying);

            ImGuiHelper::pushDisabled(!m_isPlaying);
            if (ImGuiHelper::drawClickableText("##stop", ICON_FA_STOP))
            {
                m_isPlaying = false;
                m_scene->onStopRuntime();
                ImGuiHelper::pushDisabled();
            }
            ImGuiHelper::popDisabled(!m_isPlaying);

            ImGui::EndMainMenuBar();
        }

        ImGui::PopStyleVar(2);

        m_sceneHierarchyPanel.onImGuiRender();
        m_inspectorPanel.onImGuiRender();

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
        m_editorCamera.onEvent(event); //
    }

} // namespace Varak
