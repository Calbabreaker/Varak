#include "vrpch.h"

#include "varak/core/application.h"

#include "varak/renderer/renderer.h"

#include <GLFW/glfw3.h>

namespace Varak {

    Application* Application::s_instance = nullptr;

    Application::Application(const std::string& name)
    {
        VR_PROFILE_FUNCTION();

        VR_CORE_ASSERT_MSG(!s_instance, "Aplication already exists!");
        s_instance = this;

        m_window = Window::create(WindowProperties(name));
        m_window->setEventCallback(VR_BIND_EVENT_FUNC(Application::onEvent));

        Renderer::init();

        m_imGuiLayer = new ImGuiLayer();
        pushOverlay(m_imGuiLayer);
    }

    Application::~Application()
    {
        VR_PROFILE_FUNCTION();

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

                m_imGuiLayer->begin();
                {
                    VR_PROFILE_SCOPE("layerStack onImGuiRender - Application::run");

                    for (Layer* layer : m_layerStack)
                        layer->onImGuiRender();
                }
                m_imGuiLayer->end();
            }

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        VR_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowClosedEvent>(VR_BIND_EVENT_FUNC(Application::onWindowClosed));
        dispatcher.dispatch<WindowResizedEvent>(VR_BIND_EVENT_FUNC(Application::onWindowResized));

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

    void Application::close()
    {
        m_running = false; //
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
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
