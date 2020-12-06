#include "vrpch.h"

#include "imgui_helper.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace Varak {

    namespace ImGuiHelper {

        void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
        {
            ImGuiIO& io = ImGui::GetIO();
            auto boldFont = io.Fonts->Fonts[0];

            ImGui::PushID(label.c_str());

            ImGui::Columns(2, (const char*)0, false);
            ImGui::SetColumnWidth(0, columnWidth);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

            ImGui::PushFont(boldFont);
            ImGui::Text("X");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::Text("Y");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::Text("Z");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();

            ImGui::Columns(1);

            ImGui::PopID();
        }

        bool drawInputText(std::string& text, const ImVec2& size, ImGuiInputTextFlags flags, int id)
        {
            bool returnVal = false;

            ImGui::PushID(id);
            char buffer[256];
            memset(buffer, 0, sizeof(char));
            std::strncpy(buffer, text.c_str(), sizeof(buffer));

            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
            if (ImGui::InputTextEx("##text", NULL, buffer, sizeof(buffer), size, flags, NULL, NULL))
            {
                text = std::string(buffer);
                returnVal = true;
            }

            ImGui::PopStyleVar();
            ImGui::PopID();
            return returnVal;
        }

    } // namespace ImGuiHelper

} // namespace Varak
