#pragma once

#include "window.h"

namespace Varak
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = false;
    };

    // client will define
    Application* createApplication();

} // namespace Varak