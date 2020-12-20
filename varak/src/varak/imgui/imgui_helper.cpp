#include "vrpch.h"

#include "imgui_helper.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

constexpr float disabledAlphaMult = 0.3f;

constexpr float labelIndentWidth = 120.0f;

namespace Varak {

    namespace ImGuiHelper {

        void pushDisabled(bool disabled)
        {
            if (disabled)
            {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * disabledAlphaMult);
            }
        }

        void popDisabled(bool disabled)
        {
            if (disabled)
            {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }
        }

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
            ImGui::PushID(label.data());
            bool hasInputed = false;

            // draw label if text is visible
            ImVec2 textSize = ImGui::CalcTextSize(label.data(), nullptr, true);
            if (textSize.x > 0.0f)
            {
                drawLabel(label);
                ImGui::SetColumnWidth(0, labelIndentWidth);
                ImGui::NextColumn();
            }

            // span availiable width
            ImGui::PushItemWidth(-1);
            hasInputed = func();
            ImGui::PopItemWidth();
            ImGui::Columns(1);
            ImGui::PopID();
            return hasInputed;
        }

        bool drawVec3Control(std::string_view label, glm::vec3& values, float resetValue)
        {
            return inputWithLabel(label, [&]() {
                bool hasInputed = false;

                ImGuiIO& io = ImGui::GetIO();
                ImGuiStyle& style = ImGui::GetStyle();
                ImFont* boldFont = io.Fonts->Fonts[0];

                ImGui::BeginGroup();
                ImGui::PushMultiItemsWidths(3,
                                            ImGui::CalcItemWidth() - boldFont->FontSize * 3.0f - style.ItemSpacing.x);

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

                ImGui::EndGroup();
                return hasInputed;
            });
        }

        bool drawInputText(std::string_view label, std::string& text, ImGuiInputTextFlags flags)
        {
            return inputWithLabel(label, [&]() {
                char buffer[256];
                memset(buffer, 0, sizeof(char));
                std::strncpy(buffer, text.c_str(), sizeof(buffer));

                bool hasInputed = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                hasInputed = ImGui::InputText("", buffer, sizeof(buffer), flags);
                ImGui::PopStyleVar();

                if (hasInputed)
                    text = std::string(buffer);

                return hasInputed;
            });
        }

        bool drawCheckbox(std::string_view label, bool& value)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::Checkbox("", &value); //
            });
        }

        bool drawComboBegin(std::string_view label, std::string_view previewValue, ImGuiComboFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::BeginCombo("", previewValue.data(), flags); //
            });
        }

        bool drawDragFloat(std::string_view label, float& value, float speed, float min, float max,
                           std::string_view format, ImGuiSliderFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::DragFloat("", &value, speed, min, max, format.data(), flags); //
            });
        }

        bool drawColorEdit4(std::string_view label, glm::vec4& values, ImGuiColorEditFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::ColorEdit4("", glm::value_ptr(values), flags); //
            });
        }

        bool drawClickableText(std::string_view label, std::string_view text)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

                bool hasInputed = false;
                hasInputed = ImGui::Button(text.data());

                ImGui::PopStyleColor(3);

                return hasInputed;
            });
        }

    } // namespace ImGuiHelper

} // namespace Varak
