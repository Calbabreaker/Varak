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
            for (Layer* layer : m_layerStack)
                layer->onUpdate();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowClosedEvent>(
            VR_BIND_EVENT_FUNC(Application::onWindowClosed));

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
        {
            if (event.handled)
                break;
            (*it)->onEvent(event);
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        m_layerStack.pushLayer(layer); //
    }

    void Application::pushOverlay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay); //
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_running = false;
        return true;
    }

} // namespace Varak