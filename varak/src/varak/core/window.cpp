#include "varak/core/window.h"

#include "varak/core/platform_detection.h"
#ifdef VR_PLATFORM_WINDOWS
    #include "platform/windows/windows_window.h"
#endif

namespace Varak {

    std::unique_ptr<Window> Window::create(const WindowProps& props)
    {
#ifdef VR_PLATFORM_WINDOWS
        return std::make_unique<WindowsWindow>(props);
#endif
    }

} // namespace Varak