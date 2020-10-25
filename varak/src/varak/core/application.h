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

    private:
        bool onWindowClosed(WindowClosedEvent& event);

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = false;
        LayerStack m_layerStack;
    };

    // client will define
    Application* createApplication();

} // namespace Varak