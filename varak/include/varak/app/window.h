#pragma once

#include "varak/event/event.h"
#include "varak/renderer/rendering_context.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

namespace Varak {

    struct WindowProperties
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProperties(const std::string& p_title = "Varak Engine", uint32_t p_width = 1280,
                         uint32_t p_height = 720)
            : title(p_title), width(p_width), height(p_height)
        {
        }
    };

    class Window
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        Window(const WindowProperties& props);
        ~Window();

        void onUpdate();

        uint32_t getWidth() const { return m_data.width; }
        uint32_t getHeight() const { return m_data.height; }

        void setEventCallback(const EventCallbackFunc& callback)
        {
            m_data.eventCallback = callback;
        }
        void setVSync(bool enabled);
        bool isVSync() const;

        GLFWwindow* getNativeWindow() const { return m_window; }

    private:
        GLFWwindow* m_window;

        struct WindowData
        {
            std::string title;
            uint32_t width, height;
            bool vSyncEnabled;

            EventCallbackFunc eventCallback;
        };

        WindowData m_data;
        std::unique_ptr<RenderingContext> m_context;
    };

} // namespace Varak
