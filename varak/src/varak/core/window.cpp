#include "vrpch.h"

#include "varak/core/window.h"

    #include "platform/windows/windows_window.h"

namespace Varak {

    Scope<Window> Window::create(const WindowProperties& props)
    {
        return createScope<WindowsWindow>(props);
    }

} // namespace Varak
