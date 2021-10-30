// include this only in your main app cpp file

#include "varak/app/application.h"

int main(int argc, char** argv)
{
    Varak::Log::init();

    Varak::Application* app = Varak::createApplication();
    app->run();
    delete app;
}
