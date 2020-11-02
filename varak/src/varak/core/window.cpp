#include "varak/core/window.h"

#include "varak/core/platform_detection.h"
#ifdef VR_PLATFORM_WINDOWS
    #include "platform/windows/windows_window.h"
#endif

namespace Varak {

    Scope<Window> Window::create(const WindowProps& props)
    {
#ifdef VR_PLATFORM_WINDOWS
        return makeScope<WindowsWindow>(props);
#endif
    }

} // namespace Varak