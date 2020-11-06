#include "varak/core/window.h"

#include "varak/core/platform_detection.h"
#ifdef VR_PLATFORM_WINDOWS
    #include "platform/windows/windows_window.h"
#endif

namespace Varak {

    Scope<Window> Window::create(const WindowProps& props)
    {
#if defined(VR_PLATFORM_WINDOWS)
        return createScope<WindowsWindow>(props);
#endif
    }

} // namespace Varak