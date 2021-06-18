#include "fontawesome5_icons.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_layer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>

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
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport

        io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 16.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 16.0f);

        ImFontConfig fontConfig;
        fontConfig.MergeMode = true;
        static ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        io.Fonts->AddFontFromFileTTF("assets/fonts/fontawesome/fa-solid-900.ttf", 12.0f, &fontConfig, iconRanges);

        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 2.0f;
        style.WindowRounding = 2.0f;
        style.PopupRounding = 2.0f;

        setDarkThemeColors();

        GLFWwindow* nativeWindow = Application::get().getWindow().getNativeWindow();

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

    void ImGuiLayer::beginImGui()
    {
        VR_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::endImGui()
    {
        VR_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        Window& window = Application::get().getWindow();
        io.DisplaySize = ImVec2(static_cast<float>(window.getWidth()), static_cast<float>(window.getHeight()));

        // rendering
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

    void ImGuiLayer::setDarkThemeColors()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;

        // item colours
        ImVec4 itemDefaultColor(0.20f, 0.23f, 0.27f, 1.00f);
        ImVec4 itemHoveredColor(0.27f, 0.31f, 0.36f, 1.00f);
        ImVec4 itemActiveColor(0.17f, 0.20f, 0.23f, 1.00f);

        colors[ImGuiCol_FrameBg] = itemDefaultColor;
        colors[ImGuiCol_TitleBg] = itemDefaultColor;
        colors[ImGuiCol_TitleBgCollapsed] = itemDefaultColor;
        colors[ImGuiCol_TitleBgActive] = itemDefaultColor;
        colors[ImGuiCol_Button] = itemDefaultColor;
        colors[ImGuiCol_Header] = itemDefaultColor;

        colors[ImGuiCol_FrameBgHovered] = itemHoveredColor;
        colors[ImGuiCol_ButtonHovered] = itemHoveredColor;
        colors[ImGuiCol_HeaderHovered] = itemHoveredColor;

        colors[ImGuiCol_FrameBgActive] = itemActiveColor;
        colors[ImGuiCol_ButtonActive] = itemActiveColor;
        colors[ImGuiCol_HeaderActive] = itemActiveColor;

        // window
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
        colors[ImGuiCol_Tab] = itemDefaultColor;
        colors[ImGuiCol_TabUnfocused] = itemDefaultColor;
        colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.45f, 0.51f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.29f, 0.35f, 0.39f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];

        // primary color
        ImVec4 primaryDefaultColor(0.26f, 0.59f, 0.98f, 1.00f);
        ImVec4 primaryHoveredColor(0.17f, 0.41f, 0.71f, 1.00f);
        ImVec4 primaryActiveColor(0.10f, 0.23f, 0.39f, 1.00f);
        colors[ImGuiCol_CheckMark] = primaryDefaultColor;
        colors[ImGuiCol_SliderGrab] = primaryDefaultColor;
        colors[ImGuiCol_ResizeGripActive] = primaryDefaultColor;

        colors[ImGuiCol_ResizeGripHovered] = primaryHoveredColor;

        colors[ImGuiCol_SliderGrabActive] = primaryActiveColor;
        colors[ImGuiCol_ResizeGrip] = primaryActiveColor;

        // other
        colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.16f, 0.20f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
    }

} // namespace Varak
