#pragma once

#include "layer_stack.h"
#include "varak/events/window_event.h"
#include "window.h"

namespace Varak
{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        static Application& get() { return *s_instance; }
        Window& getWindow() { return *m_window; }

    private:
        bool onWindowClosed(WindowClosedEvent& event);

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = false;
        LayerStack m_layerStack;
        static Application* s_instance;
    };

    // client will define
    Application* createApplication();

} // namespace Varak