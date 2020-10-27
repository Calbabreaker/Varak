#pragma once

#include "key_codes.h"
#include "mouse_codes.h"

namespace Varak
{
    class Input
    {
    public:
        static bool isKeyPressed(KeyCode key);
        static bool isMouseButtonPressed(MouseCode button);

        static float getMouseX();
        static float getMouseY();
    };

} // namespace Varak