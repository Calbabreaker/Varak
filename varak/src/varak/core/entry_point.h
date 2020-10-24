#pragma once

#include "log.h"
#include "platform_detection.h"

#ifdef VR_PLATFORM_WINDOWS

extern Varak::Application* Varak::createApplication();

int main(int argc, char** argv)
{
    Varak::Log::init();

    #ifdef VR_DEBUG
    VR_CORE_INFO("Hello");
    VR_CORE_CRITICAL("no");
    #endif

    VR_CORE_INFO("Hi");

    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}

#endif