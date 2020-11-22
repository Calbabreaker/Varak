#pragma once

#include "varak/core/base.h"
#include "varak/events/event.h"

namespace Varak {

    struct WindowProperties
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProperties(const std::string& title = "Varak Engine", uint32_t width = 1280, uint32_t height = 720)
            : title(title), width(width), height(height)
        {
        }
    };

    class Window
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void onUpdate() = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setEventCallback(const EventCallbackFunc& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        static Scope<Window> create(const WindowProperties& props = WindowProperties());

        virtual void* getNativeWindow() const = 0;
    };

} // namespace Varak
