#include "inspector_panel.h"
#include "varak_imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    template <typename Component, typename UIFunc>
    static void drawComponent(const std::string& name, Entity entity, UIFunc uiFunc)
    {
        ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
            ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
            ImGuiTreeNodeFlags_FramePadding;
        if (entity.hasComponent<Component>())
        {
            auto& component = entity.getComponent<Component>();
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
            float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;
            ImGui::Separator();
            bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(Component).hash_code()),
                                            treeNodeFlags, "%s", name.c_str());
            ImGui::PopStyleVar();

            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right) ||
                ImGuiHelper::drawClickableText("##extra", ICON_FA_ELLIPSIS_V,
                                               ImVec2(lineHeight, lineHeight)))
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
            ImGuiHelper::drawInputText("##name", entity.getComponent<IdentifierComponent>().name);
        }

        drawComponent<TransformComponent>("Transform", entity, [](TransformComponent& transform) {
            ImGuiHelper::drawVec3Control("Translation", transform.translation);

            glm::vec3 rotation = glm::degrees(transform.rotation);
            if (ImGuiHelper::drawVec3Control("Rotation", rotation))
                transform.rotation = glm::radians(rotation);

            ImGuiHelper::drawVec3Control("Scale", transform.scale, 1.0f);
        });

        drawComponent<CameraComponent>("Camera", entity, [](CameraComponent& camera) {
            ImGuiHelper::drawCheckbox("Primary", camera.primary);
            constexpr const char* projectionTypeStrings[] = { "Perpective", "Orthographic" };
            const char* currentProjectionTypeString =
                projectionTypeStrings[static_cast<int>(camera.projectionType)];

            if (ImGuiHelper::drawComboBegin("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < std::size(projectionTypeStrings); i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        camera.projectionType = static_cast<Camera::ProjectionType>(i);
                        break;
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (camera.projectionType == Camera::ProjectionType::Perpective)
            {
                float perpectiveFOV = glm::degrees(camera.perpectiveFOV);
                if (ImGuiHelper::drawDragFloat("FOV", perpectiveFOV))
                    camera.perpectiveFOV = glm::radians(perpectiveFOV);

                ImGuiHelper::drawDragFloat("Near", camera.perpectiveNear);
                ImGuiHelper::drawDragFloat("Far", camera.perpectiveFar);
            }
            else if (camera.projectionType == Camera::ProjectionType::Orthographic)
            {
                ImGuiHelper::drawDragFloat("Size", camera.orthographicSize);
                ImGuiHelper::drawDragFloat("Near", camera.orthographicNear);
                ImGuiHelper::drawDragFloat("Far", camera.orthographicFar);
                ImGuiHelper::drawCheckbox("Fixed Aspect Ratio", camera.fixedAspectRatio);
            }
        });

        drawComponent<SpriteRendererComponent>(
            "Sprite Renderer", entity, [](SpriteRendererComponent& sprite) {
                ImGuiHelper::drawColorEdit4("Color", sprite.color); //
            });
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

        // Add Component button
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 10.0f));
        ImGui::Separator();

        float availWidth = ImGui::GetContentRegionAvail().x;
        ImVec2 buttonSize(availWidth / 2.0f, 0.0f);
        ImGui::Indent(availWidth / 2.0f - buttonSize.x / 2.0f);

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
