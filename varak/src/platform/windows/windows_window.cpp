#include "windows_window.h"
#include "varak/events/key_event.h"
#include "varak/events/mouse_event.h"
#include "varak/events/window_event.h"

namespace Varak
{
    static bool s_glfwInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        VR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        init(props); //
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown(); //
    }

    void WindowsWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        glfwSwapInterval(enabled);
        m_data.vSyncEnabled = enabled;
    }

    bool WindowsWindow::isVSync() const { return m_data.vSyncEnabled; }

    void WindowsWindow::init(const WindowProps& props)
    {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        VR_CORE_INFO("Creating window: {0} ({1} by {2})", m_data.title,
                     m_data.width, m_data.height);

        if (!s_glfwInitialized)
        {
            int success = glfwInit();
            VR_CORE_ASSERT(success, "Could not initialize GLFW");
            s_glfwInitialized = true;
        }

        m_window = glfwCreateWindow(static_cast<int>(m_data.width),
                                    static_cast<int>(m_data.height),
                                    m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // clang-format off

        // set glfw callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) 
        {
                WindowData& data = *reinterpret_cast<WindowData*>(
                    glfwGetWindowUserPointer(window));
                data.width = width;
                data.height = height;

                WindowResizedEvent event(width, height);
                data.eventCallback(event);
            });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            WindowClosedEvent event;
            data.eventCallback(event);
        });

        glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            if (focus)
            {
                WindowFocusEvent event;
                data.eventCallback(event);
            } else
            {
                WindowLostFocusEvent event;
                data.eventCallback(event);
            }
        });

        // missing window move

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE: 
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(static_cast<float>(xOffset),
                                        static_cast<float>(yOffset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) 
        {
            WindowData& data = *reinterpret_cast<WindowData*>(
                glfwGetWindowUserPointer(window));

            MouseMovedEvent event(static_cast<float>(xPos),
                                static_cast<float>(yPos));
            data.eventCallback(event);
        });

        // clang-format on
    }

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(m_window); //
    }

} // namespace Varak