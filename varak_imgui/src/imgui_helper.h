#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <string>
#include <string_view>

namespace Varak {

    namespace ImGuiHelper {

        // disables items within push and pop
        void pushDisabled(bool disabled = true);
        void popDisabled(bool disabled = true);

        // label on left side instead of right for imgui
        void drawLabel(std::string_view label);

        // functions here to make it easier draw stuff
        bool drawVec3Control(std::string_view label, glm::vec3& values, float resetValue = 0.0f);
        bool drawInputText(std::string_view label, std::string& text,
                           ImGuiInputTextFlags flags = 0);
        bool drawCheckbox(std::string_view label, bool& value);
        bool drawComboBegin(std::string_view label, std::string_view previewValue,
                            ImGuiComboFlags flags = 0);
        bool drawDragFloat(std::string_view label, float& value, float speed = 1.0f,
                           float min = 0.0f, float max = 0.0f, std::string_view format = "%.3f",
                           ImGuiSliderFlags flags = 0);
        bool drawColorEdit4(std::string_view label, glm::vec4& values,
                            ImGuiColorEditFlags flags = 0);
        bool drawClickableText(std::string_view label, std::string_view text,
                               const ImVec2& sizeArg = ImVec2(0.0f, 0.0f),
                               ImGuiButtonFlags flags = 0);

    } // namespace ImGuiHelper

} // namespace Varak
