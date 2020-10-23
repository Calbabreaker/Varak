#pragma once

#include "platform_detection.h"
#include "application.h"

#ifdef VR_PLATFORM_WINDOWS

int main(int argc, const char* argv)
{
    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}

#endif