#pragma once

#include "platform_detection.h"
#include "base.h"

#ifdef VR_PLATFORM_WINDOWS

extern Varak::Application* Varak::createApplication();

int main(int argc, char** argv)
{
    Varak::Log::init();

    VR_CORE_ASSERT(false, "rip");

    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}

#endif