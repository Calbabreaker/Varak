#include "application.h"
#include "varak/events/key_event.h"

namespace Varak
{
    Application::Application()
    {
        m_window = Window::create();
        m_running = true;
    }

    Application::~Application() {}

    void Application::run()
    {
        while (m_running)
        {
            m_window->onUpdate();
        }
    }

} // namespace Varak