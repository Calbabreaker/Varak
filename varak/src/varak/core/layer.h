#pragma once

#include "varak/core/timestep.h"
#include "varak/events/event.h"

namespace Varak {

    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep ts) {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event& event) {}
    };

} // namespace Varak