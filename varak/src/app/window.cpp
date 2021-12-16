#include "varak/app/window.h"
#include "varak/event/key_event.h"
#include "varak/event/mouse_event.h"
#include "varak/event/window_event.h"
#include "varak/renderer/renderer.h"
#include "varak/renderer/renderer_api.h"

namespace Varak {

    static uint8_t s_glfwWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        VR_CORE_ASSERT_RELEASE(error != GLFW_VERSION_UNAVAILABLE,
                               "OpenGL version must be at least 4.5!");
        VR_CORE_ASSERT_RELEASE(false, "GLFW Error ({}): {}", error, description);
    }

    Window::Window(const WindowProperties& props)
    {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        VR_CORE_INFO("Creating window: '{}' ({} by {}). Count: {}", m_data.title, m_data.width,
                     m_data.height, s_glfwWindowCount + 1);

        if (s_glfwWindowCount == 0)
        {
            int success = glfwInit();
            VR_CORE_ASSERT_MSG(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        if (Renderer::getAPI() == RendererAPI::API::OpenGL)
        {
            // make glfw use OpenGL 4.5
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if VR_DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
        }

        m_handle = glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height),
                                    m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_handle);

        VR_CORE_ASSERT_MSG(m_handle, "Could not create Window!");
        s_glfwWindowCount++;

        glfwSetWindowUserPointer(m_handle, &m_data);
        setVSync(true);

        // set glfw callbacks
        glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* handle, int width, int height) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));
            data.width = static_cast<uint32_t>(width);
            data.height = static_cast<uint32_t>(height);

            WindowResizedEvent event(data.width, data.height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* handle) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

            WindowClosedEvent event;
            data.eventCallback(event);
        });

        glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* handle, int focus) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

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

        glfwSetKeyCallback(
            m_handle, [](GLFWwindow* handle, int key, int /*scancode*/, int action, int /*mods*/) {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

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

        glfwSetCharCallback(m_handle, [](GLFWwindow* handle, unsigned int keycode) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(
            m_handle, [](GLFWwindow* handle, int button, int action, int /*mods*/) {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

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

        glfwSetScrollCallback(m_handle, [](GLFWwindow* handle, double xOffset, double yOffset) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

            MouseScrolledEvent event({ static_cast<float>(xOffset), static_cast<float>(yOffset) });
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_handle, [](GLFWwindow* handle, double xPos, double yPos) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

            glm::vec2 position = { static_cast<float>(xPos), static_cast<float>(yPos) };
            static glm::vec2 lastMousePos = position;
            glm::vec2 offset = position - lastMousePos;
            lastMousePos = position;

            MouseMovedEvent event(offset);
            data.eventCallback(event);
        });
    }

    Window::~Window()
    {
        VR_CORE_INFO("Destroying window '{}'...", m_data.title);
        glfwDestroyWindow(m_handle);
        s_glfwWindowCount--;

        if (s_glfwWindowCount == 0)
            glfwTerminate();
    }

    void Window::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_handle);
    }

    void Window::setVSync(bool enabled)
    {
        glfwSwapInterval(enabled);
        m_data.vSyncEnabled = enabled;
    }

    bool Window::isVSync() const
    {
        return m_data.vSyncEnabled; //
    }

} // namespace Varak
