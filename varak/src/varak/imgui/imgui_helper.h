#pragma once

#include <glm/glm.hpp>

#include <imgui.h>
#include <string>

namespace Varak {

    namespace ImGuiHelper {

        void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f,
                             float columnWidth = 100.0f);

        bool drawInputText(std::string& name, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, int id = 0);

    } // namespace ImGuiHelper

} // namespace Varak
