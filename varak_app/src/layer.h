#pragma once

#include "timestep.h"
#include "varak_event.h"

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
