#include "varak/imgui/imgui_layer.h"

#include "varak/core/application.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Varak {

    ImGuiLayer::ImGuiLayer() {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        VR_PROFILE_FUNCTION();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport 

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so
        // platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(nativeWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
        VR_PROFILE_FUNCTION();

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event)
    {
        if (m_blockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            event.handled |= event.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            event.handled |= event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::begin()
    {
        VR_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        VR_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        Window& window = Application::get().getWindow();
        io.DisplaySize = ImVec2(static_cast<float>(window.getWidth()), static_cast<float>(window.getHeight()));

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

} // namespace Varak
