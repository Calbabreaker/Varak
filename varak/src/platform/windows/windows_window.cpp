#include "vrpch.h"

#include "platform/windows/windows_window.h"

#include "varak/events/key_event.h"
#include "varak/events/mouse_event.h"
#include "varak/events/window_event.h"

#include "varak/renderer/renderer.h"

namespace Varak {

    static uint8_t s_glfwWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        VR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& props)
    {
        VR_PROFILE_FUNCTION();

        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        VR_CORE_INFO("Creating window: {0} ({1} by {2}). Count: {3}", m_data.title, m_data.width, m_data.height,
                     s_glfwWindowCount + 1);

        if (s_glfwWindowCount == 0)
        {
            VR_PROFILE_SCOPE("glfwInit - WindowsWindow::WindowsWindow");

            int success = glfwInit();
            VR_CORE_ASSERT_MSG(success, "Could not initialize GLFW");
        }

        {
            VR_PROFILE_SCOPE("glfwCreateWindow - WindowsWindow::WindowsWindow");

            if (Renderer::getAPI() == RendererAPI::API::OpenGL) 
            {
                // make glfw use OpenGL 4.5
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef VR_DEBUG
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
            }

            m_window = glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height),
                                        m_data.title.c_str(), nullptr, nullptr);

            VR_CORE_ASSERT_MSG(m_window, "Could not create Window!");
            s_glfwWindowCount++;
        }

        m_context = RenderingContext::create(m_window);
        m_context->init();

        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // set glfw callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.width = width;
            data.height = height;

            WindowResizedEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowClosedEvent event;
            data.eventCallback(event);
        });

        glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            if (focus)
            {
                WindowFocusEvent event;
                data.eventCallback(event);
            }
            else
            {
                WindowLostFocusEvent event;
                data.eventCallback(event);
            }
        });

        // missing window move

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                data.eventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(static_cast<KeyCode>(key));
                data.eventCallback(event);
                break;
            }

            case GLFW_REPEAT:
            {
                KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                data.eventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event({ static_cast<float>(xOffset), static_cast<float>(yOffset) });
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            glm::vec2 position = { static_cast<float>(xPos), static_cast<float>(yPos) };
            static glm::vec2 lastMousePos = position;
            glm::vec2 offset = position - lastMousePos;
            lastMousePos = position;

            MouseMovedEvent event(offset);
            data.eventCallback(event);
        });
    }

    WindowsWindow::~WindowsWindow()
    {
        VR_PROFILE_FUNCTION();

        glfwDestroyWindow(m_window);
        s_glfwWindowCount--;

        if (s_glfwWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::onUpdate()
    {
        VR_PROFILE_FUNCTION();

        glfwPollEvents();
        m_context->swapBuffers();
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        VR_PROFILE_FUNCTION();

        glfwSwapInterval(enabled);
        m_data.vSyncEnabled = enabled;
    }

    bool WindowsWindow::isVSync() const
    {
        return m_data.vSyncEnabled; //
    }

} // namespace Varak
