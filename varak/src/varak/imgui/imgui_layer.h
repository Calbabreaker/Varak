#pragma once

#include "varak/core/layer.h"

#include "varak/events/key_event.h"
#include "varak/events/mouse_event.h"

#include <imgui.h>

namespace Varak {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        virtual void onEvent(Event& event) override;

        void begin();
        void end();

        void blockEvents(bool block) { m_blockEvents = block; }

    private:
        bool m_blockEvents = false;
    };

} // namespace Varak
