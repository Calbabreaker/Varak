#include "application.h"
#include "varak/events/window_event.h"
#include "log.h"

namespace Varak
{
    Application::Application() {}
    Application::~Application() {}

    void Application::run()
    {
        WindowClosedEvent event;
        if (event.isInCategory(EventCategory::Window))
            VR_CORE_TRACE(event);

        while (true)
        {
        }
    }

} // namespace Varak