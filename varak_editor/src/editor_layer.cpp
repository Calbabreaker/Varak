#include "editor_layer.h"

#include "varak/app/application.h"
#include "varak/imgui/fontawesome5_icons.h"
#include "varak/imgui/imgui_helper.h"
#include "varak/renderer/renderer2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

#include <imgui.h>

namespace Varak {

    EditorLayer::EditorLayer(ImGuiLayer* imguiLayer)
        : m_sceneHierarchyPanel(&m_inspectorPanel), m_imguiLayer(imguiLayer)
    {
    }

    void EditorLayer::onAttach()
    {
        if (!std::filesystem::exists("imgui.ini"))
            std::filesystem::copy("assets/imgui-default.ini", "imgui.ini");

        Window& window = Application::get().getWindow();
        uint32_t width = window.getWidth();
        uint32_t height = window.getHeight();

        m_editorCamera.setViewportSize(width, height);

        FrameBufferProperties props;
        props.width = width;
        props.height = height;
        m_frameBuffer = FrameBuffer::create(props);

        m_scene = std::make_shared<Scene>(width, height);
        m_sceneHierarchyPanel.setScene(m_scene);

        m_squareEntity = m_scene->createEntity();
        m_squareEntity.addComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        m_cameraEntity = m_scene->createEntity("Camera");
        m_cameraEntity.addComponent<CameraComponent>();
    }

    void EditorLayer::onDetach() {}

    void EditorLayer::onUpdate(Timestep ts)
    {
        if (m_viewportFocused)
            m_editorCamera.onUpdate(ts);

        m_scene->onUpdate(ts);
    }

    void EditorLayer::onRender()
    {
        m_frameBuffer->bind();
        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::clear();

        if (m_isPlaying)
            m_scene->onRenderRuntime();
        else
            m_scene->onRenderEditor(m_editorCamera);

        m_frameBuffer->unbind();

        // imgui render stuff
        m_imguiLayer->beginImGui();

        static bool dockSpaceOpen = true;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;
        ImGuiIO& io = ImGui::GetIO();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::Begin("DockSpace", &dockSpaceOpen, windowFlags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        // DockSpace
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 300.0f, 50.0f });
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspaceId, { 0.0f, 0.0f }, ImGuiDockNodeFlags_None);
        }

        ImGui::PopStyleVar();

        // Menu Bar
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 8.0f, 8.0f });
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
            ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 2.0f -
                                 ImGui::CalcTextSize(ICON_FA_PLAY).x * 2.0f);
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

        const Renderer2D::Statistics& stats = Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getVertexCount());
        ImGui::Text("Indices: %d", stats.getIndexCount());

        ImGui::End(); // Stats

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::Begin("Viewport");

        m_viewportFocused = ImGui::IsWindowFocused();
        m_viewportHovered = ImGui::IsWindowHovered();
        m_imguiLayer->blockEvents(!m_viewportHovered || !m_viewportFocused);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        // resize if viewport size changed
        if (viewportSize.x > 0.0f && viewportSize.y > 0.0f)
        {
            FrameBufferProperties props = m_frameBuffer->getProperties();
            uint32_t width = static_cast<uint32_t>(viewportSize.x);
            uint32_t height = static_cast<uint32_t>(viewportSize.y);

            if (props.width != width || props.height != height)
            {
                m_frameBuffer->resize(width, height);
                m_editorCamera.setViewportSize(width, height);
                m_scene->onViewportResize(width, height);
            }
        }

        uint64_t handle = m_frameBuffer->getColorAttachmentHandle();
        ImGui::Image(reinterpret_cast<void*>(handle), viewportSize, { 0.0f, 1.0f }, { 1.0f, 0.0f });

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();

        ImGui::End(); // Dockspace

        m_imguiLayer->endImGui();
        Renderer2D::resetStats();
    }

    void EditorLayer::onEvent(Event& event)
    {
        m_editorCamera.onEvent(event); //
    }

} // namespace Varak
