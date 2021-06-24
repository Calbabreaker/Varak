#pragma once

#include "varak_event.h"

#include <glm/glm.hpp>

namespace Varak {

    class Input
    {
    public:
        static bool isKeyPressed(KeyCode key);
        static bool isMouseButtonPressed(MouseCode button);

        static glm::vec2 getMousePosition();
        static float getMouseX();
        static float getMouseY();
    };

} // namespace Varak
