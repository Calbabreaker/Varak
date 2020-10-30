#pragma once

#include "varak/core/layer_stack.h"
#include "varak/core/window.h"

#include "varak/events/window_event.h"
#include "varak/imgui/imgui_layer.h"

namespace Varak {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        static Application& get() { return *s_instance; }
        Window& getWindow() { return *m_window; }

    private:
        bool onWindowClosed(WindowClosedEvent& event);

    private:
        std::unique_ptr<Window> m_window;
        ImGuiLayer* m_imGuiLayer;
        LayerStack m_layerStack;
        static Application* s_instance;

        bool m_running = false;
    };

    // client will define
    Application* createApplication();

} // namespace Varak