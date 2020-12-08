#pragma once

#include <glm/glm.hpp>

#include <imgui.h>
#include <string>
#include <string_view>

namespace Varak {

    namespace ImGuiHelper {

        // label on left side instead of right for imgui
        void drawLabel(std::string_view label);

        // functions here to make it easier draw stuff
        bool drawVec3Control(std::string_view label, glm::vec3& values, float resetValue = 0.0f);
        bool drawInputText(std::string& text, const std::string& label, ImGuiInputTextFlags flags = 0);
        bool drawCheckbox(const std::string& label, bool& value);
        bool drawComboBegin(const std::string& label, std::string_view previewValue, ImGuiComboFlags flags = 0);
        bool drawDragFloat(const std::string& label, float& value, float speed = 1.0f, float min = 0.0f,
                           float max = 0.0f, std::string_view format = "%.3f", ImGuiSliderFlags flags = 0);
        bool drawColorEdit4(const std::string& label, glm::vec4& values, ImGuiColorEditFlags flags = 0);

    } // namespace ImGuiHelper

} // namespace Varak
