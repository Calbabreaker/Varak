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

        void begin();
        void end();

    private:
        float m_time = 0.0f;
    };

} // namespace Varak