#pragma once

#include "varak/app/timestep.h"
#include "varak/event/event.h"

namespace Varak {

    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep /*ts*/) {}
        virtual void onRender() {}
        virtual void onEvent(Event& /*event*/) {}
    };

} // namespace Varak
