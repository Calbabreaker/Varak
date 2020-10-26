#pragma once

#include "imgui.h"
#include "varak/core/layer.h"

#include "varak/events/mouse_event.h"
#include "varak/events/key_event.h"

namespace Varak
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& event) override;

        bool onMouseMoved(MouseMovedEvent& event);
        bool onMouseScrolled(MouseScrolledEvent& event);
        bool onMouseButtonPressed(MouseButtonPressedEvent& event);
        bool onMouseButtonReleased(MouseButtonReleasedEvent& event);
        bool onKeyPressed(KeyPressedEvent& event);
        bool onKeyReleased(KeyReleasedEvent& event);
        bool onKeyTyped(KeyTypedEvent& event);

    private:
        float m_time = 0.0f;
    };

} // namespace Varak