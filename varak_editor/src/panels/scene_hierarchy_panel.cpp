#include "vrpch.h"

#include "../editor_gui.h"
#include "varak/imgui/imgui_layer.h"

#include "scene_hierarchy_panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    void SceneHierarchyPanel::setScene(const Ref<Scene>& scene)
    {
        m_scene = scene; //
    }

    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::Begin("Hierarchy");

        m_scene->m_registry.each([&](entt::entity entityID) {
            Entity entity(entityID, m_scene.get());
            drawEntityNode(entity);
        });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_selectedEntity = {};

        ImGuiPopupFlags popupFlags = ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;
        if (ImGui::BeginPopupContextWindow(0, popupFlags))
        {
            if (ImGui::MenuItem("Create Empty"))
                m_scene->createEntity();

            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Inspector");

        if (m_selectedEntity)
        {
            drawComponents(m_selectedEntity);

            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent"))
            {
                if (!m_selectedEntity.hasComponent<CameraComponent>() && ImGui::MenuItem("Camera"))
                {
                    m_selectedEntity.addComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (!m_selectedEntity.hasComponent<SpriteRendererComponent>() && ImGui::MenuItem("Sprite Renderer"))
                {
                    m_selectedEntity.addComponent<SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& component = entity.getComponent<IdentifierComponent>();

        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        treeNodeFlags |= m_selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeNodeFlags, component.name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_selectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Destroy Entity"))
            {
                m_scene->destroyEntity(entity);
                if (entity == m_selectedEntity)
                    m_selectedEntity = {};
            }

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::drawComponents(Entity entity)
    {
        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

        if (entity.hasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(TransformComponent).hash_code()), treeNodeFlags,
                                  "Transform"))
            {
                auto& component = entity.getComponent<TransformComponent>();

                EditorGui::drawVec3Control("Translation", component.translation);
                glm::vec3 rotation = glm::degrees(component.rotation);
                EditorGui::drawVec3Control("Rotation", rotation, 0.5f);
                component.rotation = glm::radians(rotation);
                EditorGui::drawVec3Control("Scale", component.scale, 0.5f);

                ImGui::TreePop();
            }
        }

        if (entity.hasComponent<CameraComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(CameraComponent).hash_code()), treeNodeFlags,
                                  "Camera"))
            {
                auto& component = entity.getComponent<CameraComponent>();
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

                ImGui::TreePop();
            }
        }

        if (entity.hasComponent<SpriteRendererComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(SpriteRendererComponent).hash_code()), treeNodeFlags,
                                  "Sprite Renderer"))
            {
                auto& component = entity.getComponent<SpriteRendererComponent>();

                if (ImGui::Button("+"))
                    ImGui::OpenPopup("ComponentSettings");

                bool componentRemoved = false;
                if (ImGui::BeginPopup("ComponentSettings"))
                {
                    if (ImGui::MenuItem("RemoveComponent"))
                        componentRemoved = true;

                    ImGui::EndPopup();
                }

                ImGui::ColorEdit4("Color", glm::value_ptr(component.color));

                if (componentRemoved)
                {
                    entity.removeComponent<SpriteRendererComponent>();
                }

                ImGui::TreePop();
            }
        }
    }
} // namespace Varak
