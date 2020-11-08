#include "varak/core/application.h"

#include "varak/renderer/renderer.h"

#include <GLFW/glfw3.h>

namespace Varak {

    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        VR_CORE_ASSERT(!s_instance, "Aplication already exists!");
        s_instance = this;

        m_window = Window::create();
        m_window->setEventCallback(VR_BIND_EVENT_FUNC(Application::onEvent));

        Renderer::init();

        m_imGuiLayer = new ImGuiLayer();
        pushOverlay(m_imGuiLayer);

        m_running = true;
    }

    Application::~Application()
    {
        Renderer::shutdown(); //
    }

    void Application::run()
    {
        while (m_running)
        {
            float now = static_cast<float>(glfwGetTime());
            Timestep ts = now - m_lastFrameTime;
            m_lastFrameTime = now;

            for (Layer* layer : m_layerStack)
                layer->onUpdate(ts);

            m_imGuiLayer->begin();
            for (Layer* layer : m_layerStack)
                layer->onImGuiRender();
            m_imGuiLayer->end();

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
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_running = false;
        return true;
    }

} // namespace Varak
