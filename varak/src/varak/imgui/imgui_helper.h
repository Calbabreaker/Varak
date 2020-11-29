#pragma once

#include <glm/glm.hpp>

#include <string>

namespace Varak {

    namespace ImGuiHelper {

        void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f,
                             float columnWidth = 100.0f);

    }

} // namespace Varak
