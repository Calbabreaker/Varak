#pragma once

#include "varak_app.h"
#include "varak_event.h"

namespace Varak {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        void onEvent(Event& event) override;

        void beginImGui();
        void endImGui();

        void blockEvents(bool block) { m_blockEvents = block; }

        void setDarkThemeColors();

    private:
        bool m_blockEvents = false;
    };

} // namespace Varak
