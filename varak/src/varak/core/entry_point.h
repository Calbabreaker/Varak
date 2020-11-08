#pragma once

// include this only in your main sandbox app cpp file

#include "varak/core/application.h"
#include "varak/core/base.h"
#include "varak/core/platform_detection.h"

#ifdef VR_PLATFORM_WINDOWS

int main(int argc, char* argv)
{
    Varak::Log::init();

    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}

#endif
