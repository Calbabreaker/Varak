#pragma once

#include "varak/core/key_codes.h"
#include "varak/core/mouse_codes.h"

namespace Varak {

    class Input
    {
    public:
        static bool isKeyPressed(Key key);
        static bool isMouseButtonPressed(Mouse button);

        static glm::vec2 getMousePosition();
        static float getMouseX();
        static float getMouseY();
    };

} // namespace Varak