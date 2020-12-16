#include "vrpch.h"

#include "inspector_panel.h"

#include "varak/imgui/imgui_helper.h"
#include "varak/imgui/imgui_layer.h"
#include "varak/scene/components.h"
#include "varak/scene/entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace Varak {

    template <typename Component, typename UIFunc>
    static void drawComponent(const std::string& name, Entity entity, UIFunc uiFunc)
    {
        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
                                           ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
                                           ImGuiTreeNodeFlags_FramePadding;
        if (entity.hasComponent<Component>())
        {
            auto& component = entity.getComponent<Component>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
            ImGui::Separator();
            bool opened =
                ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(Component).hash_code()), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();

            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

            if (ImGui::Button("+", ImVec2(lineHeight, lineHeight)))
                ImGui::OpenPopup("ComponentSettings");

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (opened)
            {
                uiFunc(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.removeComponent<Component>();
        }
    }

    static void drawComponents(Entity entity)
    {
        if (entity.hasComponent<IdentifierComponent>())
        {
            ImGuiHelper::drawInputText("", entity.getComponent<IdentifierComponent>().name);
        }

        drawComponent<TransformComponent>("Transform", entity, [](auto& component) {
            ImGuiHelper::drawVec3Control("Translation", component.translation);

            glm::vec3 rotation = glm::degrees(component.rotation);
            if (ImGuiHelper::drawVec3Control("Rotation", rotation))
                component.rotation = glm::radians(rotation);

            ImGuiHelper::drawVec3Control("Scale", component.scale, 1.0f);
        });

        drawComponent<CameraComponent>("Camera", entity, [](auto& component) {
            Camera& camera = component.camera;

            ImGuiHelper::drawCheckbox("Primary", component.primary);
            constexpr const char* projectionTypeStrings[] = { "Perpective", "Orthographic" };
            const char* currentProjectionTypeString =
                projectionTypeStrings[static_cast<int>(camera.getProjectionType())];

            if (ImGuiHelper::drawComboBegin("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < std::size(projectionTypeStrings); i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        camera.setProjectionType(static_cast<Camera::ProjectionType>(i));
                        break;
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (camera.getProjectionType() == Camera::ProjectionType::Perpective)
            {
                float perpectiveFOV = glm::degrees(camera.getPerpectiveFOV());
                if (ImGuiHelper::drawDragFloat("FOV", perpectiveFOV))
                    camera.setPerpectiveFOV(glm::radians(perpectiveFOV));

                float perpectiveNear = camera.getPerpectiveNearClip();
                if (ImGuiHelper::drawDragFloat("Near", perpectiveNear))
                    camera.setPerpectiveNearClip(perpectiveNear);

                float perpectiveFar = camera.getPerpectiveFarClip();
                if (ImGuiHelper::drawDragFloat("Far", perpectiveFar))
                    camera.setPerpectiveFarClip(perpectiveFar);
            }
            else if (camera.getProjectionType() == Camera::ProjectionType::Orthographic)
            {
                float orthographicSize = camera.getOrthographicSize();
                if (ImGuiHelper::drawDragFloat("Size", orthographicSize))
                    camera.setOrthographicSize(orthographicSize);

                float orthographicNear = camera.getOrthographicNearClip();
                if (ImGuiHelper::drawDragFloat("Near", orthographicNear))
                    camera.setOrthographicNearClip(orthographicNear);

                float orthographicFar = camera.getOrthographicFarClip();
                if (ImGuiHelper::drawDragFloat("Far", orthographicFar))
                    camera.setOrthographicFarClip(orthographicFar);

                ImGuiHelper::drawCheckbox("Fixed Aspect Ratio", component.fixedAspectRatio);
            }
        });

        drawComponent<SpriteRendererComponent>(
            "Sprite Renderer", entity, [](auto& component) { ImGuiHelper::drawColorEdit4("Color", component.color); });
    }

    template <typename Component>
    static void addComponentMenuItem(Entity entity, const char* label)
    {
        if (!entity.hasComponent<Component>() && ImGui::MenuItem(label))
        {
            entity.addComponent<Component>();
            ImGui::CloseCurrentPopup();
        }
    }

    void InspectorPanel::drawProperties(Entity entity)
    {
        drawComponents(entity);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 10.0f));
        ImGui::Separator();

        float availWidth = ImGui::GetContentRegionAvail().x;
        ImVec2 buttonSize(availWidth / 2.0f, 0.0f);
        ImGui::Indent(availWidth / 2 - buttonSize.x / 2);

        if (ImGui::Button("Add Component", buttonSize))
            ImGui::OpenPopup("AddComponent");
        ImGui::PopStyleVar();

        if (ImGui::BeginPopup("AddComponent"))
        {
            addComponentMenuItem<CameraComponent>(entity, "Camera");
            addComponentMenuItem<SpriteRendererComponent>(entity, "Sprite Renderer");

            ImGui::EndPopup();
        }
    }

} // namespace Varak
