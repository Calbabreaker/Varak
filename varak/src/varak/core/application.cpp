#include "application.h"
#include "base.h"

#include <glad/glad.h>

namespace Varak
{
    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        VR_CORE_ASSERT(!s_instance, "Aplication already exists!");
        s_instance = this;

        m_window = Window::create();
        m_window->setEventCallback(VR_BIND_EVENT_FUNC(Application::onEvent));
        m_running = true;
    }

    Application::~Application() {}

    void Application::run()
    {
        while (m_running)
        {
            glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); it++)
        {
            if (event.handled)
                break;
            (*it)->onEvent(event);
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        m_layerStack.pushLayer(layer); //
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay); //
        overlay->onAttach();
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_running = false;
        return true;
    }

} // namespace Varak