// include this only in your main app cpp file

#include "varak/core/application.h"
#include "varak/core/base.h"

#include "varak/debug/instrumentor.h"

int main(int argc, char** argv)
{
    Varak::Log::init();

    VR_PROFILE_BEGIN_SESSION("Startup", "varak_profile-startup.json");
    Varak::Application* app = Varak::createApplication();
    VR_PROFILE_END_SESSION();

    VR_PROFILE_BEGIN_SESSION("Runtime", "varak_profile-runtime.json");
    app->run();
    VR_PROFILE_END_SESSION();

    VR_PROFILE_BEGIN_SESSION("Shutdown", "varak_profile-shutdown.json");
    delete app;
    VR_PROFILE_END_SESSION();
}
