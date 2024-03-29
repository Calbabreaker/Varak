#pragma once

#include "varak/app/layer_stack.h"
#include "varak/app/window.h"
#include "varak/event/window_event.h"
#include "varak/renderer/renderer.h"

#include <string>

namespace Varak {

    class Application
    {
    public:
        Application(const WindowProperties& windowProperties = WindowProperties("Varak Engine"));
        virtual ~Application();

        void run();

        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        void close();

        Window& getWindow() { return *m_window; }
        static Application& get() { return *s_instance; }

    private:
        bool onWindowClosed(WindowClosedEvent& event);
        bool onWindowResized(WindowResizedEvent& event);

    private:
        std::unique_ptr<Window> m_window;
        LayerStack m_layerStack;
        static Application* s_instance;

        bool m_running = true;
        bool m_minimized = false;
        float m_lastFrameTime = 0.0f;
    };

    // client will define
    Application* createApplication();

} // namespace Varak
