#include "windows_window.h"

namespace Varak
{
    static bool s_glfwInitialized = false;

    WindowsWindow::WindowsWindow(const WindowProps& props) { init(props); }

    WindowsWindow::~WindowsWindow() { shutdown(); }

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
    }

    void WindowsWindow::shutdown() { glfwDestroyWindow(m_window); }

} // namespace Varak