#pragma once

#include <glm/glm.hpp>

namespace Varak {

    namespace EditorGui {

        void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f,
                             float columnWidth = 100.0f);

    }

} // namespace Varak
