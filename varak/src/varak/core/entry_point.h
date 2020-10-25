#pragma once

#include "base.h"
#include "platform_detection.h"

#ifdef VR_PLATFORM_WINDOWS

extern Varak::Application* Varak::createApplication();

int main(int argc, char** argv)
{
    Varak::Log::init();

    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}

#endif