#include "imgui_layer.h"
#include "platform/opengl/imgui_opengl_renderer.h"
#include "varak/core/application.h"

#include <GLFW/glfw3.h>

namespace Varak
{

    ImGuiLayer::ImGuiLayer() {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // will use Varak keycodes soon
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach() {}

    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Window& window = Application::get().getWindow();
        io.DisplaySize = ImVec2(window.getWidth(), window.getHeight());

        float now = static_cast<float>(glfwGetTime());
        io.DeltaTime = m_time > 0.0f ? (now - m_time) : (1.0f / 60.0f);
        m_time = now;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& event)
    {
        // clang-format off
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseMovedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onMouseMoved));
        dispatcher.dispatch<MouseScrolledEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onMouseScrolled));
        dispatcher.dispatch<MouseButtonPressedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onMouseButtonPressed));
        dispatcher.dispatch<MouseButtonReleasedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onMouseButtonReleased));
        dispatcher.dispatch<KeyPressedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onKeyPressed));
        dispatcher.dispatch<KeyReleasedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onKeyReleased));
        dispatcher.dispatch<KeyTypedEvent>(VR_BIND_EVENT_FUNC(ImGuiLayer::onKeyTyped));
        // clang-format on
    }

    bool ImGuiLayer::onMouseMoved(MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.getX(), event.getY());
        return false;
    }

    bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.getXOffset();
        io.MouseWheel += event.getYOfset();
        return false;
    }

    bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::onKeyPressed(KeyPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = true;
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                     io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt =
            io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef VR_PLATFORM_WINDOWS
        io.KeySuper = false;
#else
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
        return false;
    }

    bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::onKeyTyped(KeyTypedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(event.getKeyCode());
        return false;
    }

} // namespace Varak