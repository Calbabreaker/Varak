#pragma once

namespace Varak
{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    // client will define
    Application* createApplication();

} // namespace Varak