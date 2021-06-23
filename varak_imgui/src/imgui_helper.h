#pragma once

#include <array>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <string>

namespace Varak {

    namespace ImGuiHelper {

        // disables items within push and pop
        void pushDisabled(bool disabled = true);
        void popDisabled(bool disabled = true);

        // label on left side instead of right for imgui
        void drawLabel(const char* label);

        // functions here to make it easier draw stuff
        bool drawVec3Control(const char* label, glm::vec3& values);
        template <typename T, size_t C>
        extern bool drawEnumPicker(const char* label, T& currentValue,
                                   const std::array<const char*, C>& enumNames);
        bool drawInputText(const char* label, std::string& text, ImGuiInputTextFlags flags = 0);
        bool drawCheckbox(const char* label, bool& value);
        bool drawDragFloat(const char* label, float& value, float speed = 1.0f, float min = 0.0f,
                           float max = 0.0f, const char* format = "%.3f",
                           ImGuiSliderFlags flags = 0);
        bool drawColorEdit4(const char* label, glm::vec4& values, ImGuiColorEditFlags flags = 0);
        bool drawClickableText(const char* label, const char* text,
                               const ImVec2& sizeArg = ImVec2(0.0f, 0.0f),
                               ImGuiButtonFlags flags = 0);

        template <typename T, size_t count>
        bool drawEnumPicker(const char* label, T& currentValue,
                            const std::array<const char*, count>& enumNames)
        {
            return inputWithLabel(label, [&]() {
                const char* currentValueString = enumNames[static_cast<size_t>(currentValue)];
                bool hasInputed = false;
                if (ImGui::BeginCombo(label, currentValueString))
                {
                    for (size_t i = 0; i < count; i++)
                    {
                        bool isSelected = currentValueString == enumNames[i];
                        if (ImGui::Selectable(enumNames[i], isSelected))
                        {
                            currentValue = static_cast<T>(i);
                            hasInputed = true;
                            break;
                        }

                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                return hasInputed;
            });
        }

        // this function is here to draw label with input on the left side and aligned correctly
        template <typename Func>
        bool inputWithLabel(const char* label, const Func& func)
        {
            constexpr float labelIndentWidth = 130.0f;

            ImGui::PushID(label);
            bool hasInputed = false;

            // draw label if text is visible
            ImVec2 textSize = ImGui::CalcTextSize(label, nullptr, true);
            if (textSize.x > 0.0f)
            {
                drawLabel(label);
                ImGui::SameLine(labelIndentWidth);
            }

            // span availiable width
            ImGui::PushItemWidth(-1);

            // save window to pop because of potential popup
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            hasInputed = func();

            // pop item width
            window->DC.ItemWidthStack.pop_back();
            window->DC.ItemWidth = window->DC.ItemWidthStack.empty()
                                       ? window->ItemWidthDefault
                                       : window->DC.ItemWidthStack.back();
            // pop id
            window->IDStack.pop_back();

            return hasInputed;
        }

    } // namespace ImGuiHelper

} // namespace Varak
