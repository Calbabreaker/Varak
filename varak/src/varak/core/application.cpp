#include <iostream>

#include "application.h"

namespace Varak
{
    Application::Application() {}
    Application::~Application() {}

    void Application::run()
    {
        while (true)
        {
            std::cout << "hello" << std::endl;
        }
    }
} // namespace Varak