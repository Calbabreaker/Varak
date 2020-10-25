#include "application.h"
#include "base.h"

namespace Varak
{
    Application::Application()
    {
        m_window = Window::create();
        m_window->setEventCallback(VR_BIND_EVENT_FUNC(Application::onEvent));
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

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowClosedEvent>(VR_BIND_EVENT_FUNC(Application::onWindowClosed));

        VR_CORE_TRACE("{0}", event);
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_running = false;
        return true;
    }

} // namespace Varak