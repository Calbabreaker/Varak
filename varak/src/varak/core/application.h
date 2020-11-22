#pragma once

#include "varak/core/layer_stack.h"
#include "varak/core/window.h"

#include "varak/events/window_event.h"
#include "varak/imgui/imgui_layer.h"

namespace Varak {

    class Application
    {
    public:
        Application(const std::string& name = "Varak Engine");
        virtual ~Application();

        void run();

        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        void close();

        Window& getWindow() { return *m_window; }
        ImGuiLayer* getImGuiLayer() { return m_imGuiLayer; }
        static Application& get() { return *s_instance; }

    private:
        bool onWindowClosed(WindowClosedEvent& event);
        bool onWindowResized(WindowResizedEvent& event);

    private:
        Scope<Window> m_window;
        ImGuiLayer* m_imGuiLayer;
        LayerStack m_layerStack;
        static Application* s_instance;

        bool m_running = true;
        bool m_minimized = false;
        float m_lastFrameTime = 0.0f;
    };

    // client will define
    Application* createApplication();

} // namespace Varak
