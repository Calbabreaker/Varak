#include "vrpch.h"

#include "imgui_helper.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace Varak {

    namespace ImGuiHelper {

        void drawLabel(std::string_view label)
        {
            ImGui::AlignTextToFramePadding();
            ImGui::TextEx(label.data());
            ImGui::SameLine();
        }

        // this function is here to draw label with input on the left side and aligned correctly
        template <typename Func>
        static bool inputWithLabel(std::string_view label, const Func& func)
        {
            bool hasInputed = false;
            ImVec2 textSize = ImGui::CalcTextSize(label.data());
            if (textSize.x > 0.0f)
            {
                drawLabel(label);
                ImGui::Columns(2, static_cast<const char*>(0), false);
                ImGui::SetColumnWidth(0, 120.0f);
                ImGui::NextColumn();
            }

            hasInputed = func();
            ImGui::Columns(1);
            return hasInputed;
        }

        bool drawVec3Control(std::string_view label, glm::vec3& values, float resetValue)
        {
            return inputWithLabel(label, [&]() {
                bool hasInputed = false;

                ImGuiIO& io = ImGui::GetIO();
                auto boldFont = io.Fonts->Fonts[0];

                ImGui::PushID(label.data());

                ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

                ImGui::PushFont(boldFont);
                ImGuiHelper::drawLabel("X");
                ImGui::PopFont();
                hasInputed |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();
                ImGui::SameLine();

                ImGui::PushFont(boldFont);
                ImGuiHelper::drawLabel("Y");
                ImGui::PopFont();
                hasInputed |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();
                ImGui::SameLine();

                ImGui::PushFont(boldFont);
                ImGuiHelper::drawLabel("Z");
                ImGui::PopFont();
                hasInputed |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();

                ImGui::PopID();
                return hasInputed;
            });
        }

        bool drawInputText(std::string& text, const std::string& label, ImGuiInputTextFlags flags)
        {
            return inputWithLabel(label, [&]() {
                char buffer[256];
                memset(buffer, 0, sizeof(char));
                std::strncpy(buffer, text.c_str(), sizeof(buffer));

                bool hasInputed = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                if (ImGui::InputText(("##" + label).c_str(), buffer, sizeof(buffer), flags))
                {
                    text = std::string(buffer);
                    hasInputed = true;
                }

                ImGui::PopStyleVar();
                return hasInputed;
            });
        }

        bool drawCheckbox(const std::string& label, bool& value)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::Checkbox(("##" + label).c_str(), &value); //
            });
        }

        bool drawComboBegin(const std::string& label, std::string_view previewValue, ImGuiComboFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::BeginCombo(("##" + label).c_str(), previewValue.data(), flags); //
            });
        }

        bool drawDragFloat(const std::string& label, float& value, float speed, float min, float max,
                           std::string_view format, ImGuiSliderFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::DragFloat(("##" + label).c_str(), &value, speed, min, max, format.data(), flags); //
            });
        }

        bool drawColorEdit4(const std::string& label, glm::vec4& values, ImGuiColorEditFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::ColorEdit4(("##" + label).c_str(), glm::value_ptr(values), flags); //
            });
        }

    } // namespace ImGuiHelper

} // namespace Varak
