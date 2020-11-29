#include "vrpch.h"

#include "inspector_panel.h"

#include "varak/imgui/imgui_helper.h"
#include "varak/imgui/imgui_layer.h"
#include "varak/scene/components.h"
#include "varak/scene/entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    template <typename Component, typename UIFunc>
    static void drawComponent(const std::string& name, Entity entity, UIFunc uiFunc)
    {
        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;
        if (entity.hasComponent<Component>())
        {
            auto& component = entity.getComponent<Component>();

            bool opened =
                ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(Component).hash_code()), treeNodeFlags, name.c_str());

            if (ImGui::Button("+"))
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
        drawComponent<TransformComponent>("Transform", entity, [](auto& component) {
            ImGuiHelper::drawVec3Control("Translation", component.translation);
            glm::vec3 rotation = glm::degrees(component.rotation);
            ImGuiHelper::drawVec3Control("Rotation", rotation, 0.5f);
            component.rotation = glm::radians(rotation);
            ImGuiHelper::drawVec3Control("Scale", component.scale, 0.5f);
        });

        drawComponent<CameraComponent>("Camera", entity, [](auto& component) {
            Camera& camera = component.camera;

            ImGui::Checkbox("Primary", &component.primary);

            const char* projectionTypeStrings[] = { "Perpective", "Orthographic" };
            const char* currentProjectionTypeString =
                projectionTypeStrings[static_cast<int>(camera.getProjectionType())];
            if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
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
                if (ImGui::DragFloat("FOV", &perpectiveFOV))
                    camera.setPerpectiveFOV(glm::radians(perpectiveFOV));

                float perpectiveNear = camera.getPerpectiveNearClip();
                if (ImGui::DragFloat("Near", &perpectiveNear))
                    camera.setPerpectiveNearClip(perpectiveNear);

                float perpectiveFar = camera.getPerpectiveFarClip();
                if (ImGui::DragFloat("Far", &perpectiveFar))
                    camera.setPerpectiveFarClip(perpectiveFar);
            }
            else if (camera.getProjectionType() == Camera::ProjectionType::Orthographic)
            {
                float orthographicSize = camera.getOrthographicSize();
                if (ImGui::DragFloat("Size", &orthographicSize))
                    camera.setOrthographicSize(orthographicSize);

                float orthographicNear = camera.getOrthographicNearClip();
                if (ImGui::DragFloat("Near", &orthographicNear))
                    camera.setOrthographicNearClip(orthographicNear);

                float orthographicFar = camera.getOrthographicFarClip();
                if (ImGui::DragFloat("Far", &orthographicFar))
                    camera.setOrthographicFarClip(orthographicFar);

                ImGui::Checkbox("Fixed Aspect Ratio", &component.fixedAspectRatio);
            }
        });

        drawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component) {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
        });
    }

    void InspectorPanel::drawProperties(Entity entity)
    {
        drawComponents(entity);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            if (!entity.hasComponent<CameraComponent>() && ImGui::MenuItem("Camera"))
            {
                entity.addComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (!entity.hasComponent<SpriteRendererComponent>() && ImGui::MenuItem("Sprite Renderer"))
            {
                entity.addComponent<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

} // namespace Varak
