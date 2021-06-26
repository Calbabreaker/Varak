#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_helper.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr float disabledAlphaMult = 0.3f;

namespace Varak {

    namespace ImGuiHelper {

        void pushDisabled(bool disabled)
        {
            if (disabled)
            {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha,
                                    ImGui::GetStyle().Alpha * disabledAlphaMult);
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

        void drawLabel(const char* label)
        {
            ImGui::AlignTextToFramePadding();
            ImGui::TextEx(label);
            ImGui::SameLine();
        }

        bool drawVec3Control(const char* label, glm::vec3& values)
        {
            return inputWithLabel(label, [&]() {
                bool hasInputed = false;

                ImGuiIO& io = ImGui::GetIO();
                ImGuiStyle& style = ImGui::GetStyle();
                ImFont* boldFont = io.Fonts->Fonts[0];

                ImGui::BeginGroup();
                ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth() - boldFont->FontSize * 3.0f -
                                                   style.ItemSpacing.x);

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

        bool drawInputTextBox(const char* label, std::string& text, ImGuiInputTextFlags flags)
        {
            return inputWithLabel(label, [&]() {
                char buffer[256];
                memset(buffer, 0, sizeof(char));
                std::strncpy(buffer, text.c_str(), sizeof(buffer));

                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                bool hasInputed = ImGui::InputText("", buffer, sizeof(buffer), flags);
                ImGui::PopStyleVar();

                if (hasInputed)
                    text = std::string(buffer);

                return hasInputed;
            });
        }

        bool drawCheckbox(const char* label, bool& value)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::Checkbox("", &value); //
            });
        }

        bool drawComboBegin(const char* label, const char* previewValue, ImGuiComboFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::BeginCombo("", previewValue, flags); //
            });
        }

        bool drawDragFloat(const char* label, float& value, float speed, float min, float max,
                           const char* format, ImGuiSliderFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::DragFloat("", &value, speed, min, max, format, flags); //
            });
        }

        bool drawColorEdit(const char* label, glm::vec4& values, ImGuiColorEditFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                return ImGui::ColorEdit4("", glm::value_ptr(values), flags); //
            });
        }

        bool drawClickableText(const char* label, const char* text, const ImVec2& sizeArg,
                               ImGuiButtonFlags flags)
        {
            return ImGuiHelper::inputWithLabel(label, [&]() {
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                ImGuiStyle& style = ImGui::GetStyle();
                ImGuiID id = window->GetID(text);
                ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, true);

                ImVec2 pos = window->DC.CursorPos;
                pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
                ImVec2 size = ImGui::CalcItemSize(sizeArg, textSize.x + style.FramePadding.x * 2.0f,
                                                  textSize.y + style.FramePadding.y * 2.0f);

                const ImRect bb(pos, pos + size);
                ImGui::ItemSize(size, style.FramePadding.y);
                if (!ImGui::ItemAdd(bb, id))
                    return false;

                bool hovered, held;
                bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

                // Render
                if (hovered)
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
                ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding,
                                         text, nullptr, &textSize, style.ButtonTextAlign, &bb);
                if (hovered)
                    ImGui::PopStyleColor();

                return pressed;
            });
        }

    } // namespace ImGuiHelper

} // namespace Varak
