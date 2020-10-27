#pragma once

#include "varak/core/window.h"

#include <GLFW/glfw3.h>

namespace Varak
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow();

        void onUpdate() override;

        uint32_t getWidth() const override { return m_data.width; }
        uint32_t getHeight() const override { return m_data.height; }

        void setEventCallback(const EventCallbackFunc& callback) override
        {
            m_data.eventCallback = callback;
        }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        void* getNativeWindow() const override { return m_window; }

    private:
        void init(const WindowProps& props);
        void shutdown();

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
    };

} // namespace Varak