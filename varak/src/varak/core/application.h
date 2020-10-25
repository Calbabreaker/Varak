#pragma once

#include "window.h"
#include "varak/events/window_event.h"

namespace Varak
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& event);

    private:
        bool onWindowClosed(WindowClosedEvent& event);

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = false;
    };

    // client will define
    Application* createApplication();

} // namespace Varak