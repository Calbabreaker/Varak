#pragma once

#include <glm/glm.hpp>

#include "key_codes.h"
#include "mouse_codes.h"

namespace Varak
{
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