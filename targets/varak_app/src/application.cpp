#include "application.h"
#include "src/core.h"
#include "varak_renderer.h"

#include <GLFW/glfw3.h>

namespace Varak {

    Application* Application::s_instance = nullptr;

    Application::Application(const WindowProperties& windowProperties)
    {
        VR_PROFILE_FUNCTION();

        VR_CORE_ASSERT_MSG(!s_instance, "Aplication already exists!");
        s_instance = this;

        m_window = createScope<Window>(windowProperties);
        m_window->setEventCallback(VR_BIND_FUNC(Application::onEvent));

        Renderer::init();
    }

    Application::~Application()
    {
        VR_PROFILE_FUNCTION();

        for (Layer* layer : m_layerStack)
        {
            layer->onDetach();
            delete layer;
        }

        Renderer::shutdown();
    }

    void Application::run()
    {
        VR_PROFILE_FUNCTION();

        while (m_running)
        {
            VR_PROFILE_SCOPE("Application update loop");

            float now = static_cast<float>(glfwGetTime());
            Timestep ts = now - m_lastFrameTime;
            m_lastFrameTime = now;

            if (!m_minimized)
            {
                {
                    VR_PROFILE_SCOPE("layerStack onUpdate - Application::run");
                    for (Layer* layer : m_layerStack)
                        layer->onUpdate(ts);
                }

                {
                    VR_PROFILE_SCOPE("layerStack onRender - Application::run");
                    for (Layer* layer : m_layerStack)
                        layer->onRender();
                }
            }

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        VR_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowClosedEvent>(VR_BIND_FUNC(Application::onWindowClosed));
        dispatcher.dispatch<WindowResizedEvent>(VR_BIND_FUNC(Application::onWindowResized));

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); it++)
        {
            if (event.handled)
                break;
            (*it)->onEvent(event);
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        VR_PROFILE_FUNCTION();

        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        VR_PROFILE_FUNCTION();

        m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::popLayer(Layer* layer)
    {
        VR_PROFILE_FUNCTION();

        if (m_layerStack.popLayer(layer))
            layer->onDetach();
        else
            VR_CORE_ASSERT_MSG(false, "Failed to pop layer!");
    }

    void Application::popOverlay(Layer* overlay)
    {
        VR_PROFILE_FUNCTION();

        if (m_layerStack.popLayer(overlay))
            overlay->onDetach();
        else
            VR_CORE_ASSERT_MSG(false, "Failed to pop overlay!");
    }

    void Application::close()
    {
        m_running = false; //
    }

    bool Application::onWindowClosed(WindowClosedEvent& /*event*/)
    {
        m_running = false;
        return true;
    }

    bool Application::onWindowResized(WindowResizedEvent& event)
    {
        VR_PROFILE_FUNCTION();

        if (event.getWidth() == 0 || event.getHeight() == 0)
        {
            m_minimized = true;
            return false;
        }

        m_minimized = false;
        Renderer::onWindowResized(event.getWidth(), event.getHeight());
        return false;
    }

} // namespace Varak
