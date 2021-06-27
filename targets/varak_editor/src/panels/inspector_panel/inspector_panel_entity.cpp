#include "inspector_panel.h"
#include "varak_imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    template <typename T, typename UIFunc>
    static void drawComponent(const std::string& name, Entity entity, UIFunc uiFunc)
    {
        ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
            ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
            ImGuiTreeNodeFlags_FramePadding;
        if (entity.hasComponent<T>())
        {
            T& component = entity.getComponent<T>();
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
            float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;
            bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(T).hash_code()),
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
                entity.removeComponent<T>();
        }
    }

    static void drawComponents(Entity entity)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 5.0f);

        drawComponent<TransformComponent>("Transform", entity, [](TransformComponent& transform) {
            ImGuiHelper::drawVec3Control("Translation", transform.translation);

            glm::vec3 rotation = glm::degrees(transform.rotation);
            if (ImGuiHelper::drawVec3Control("Rotation", rotation))
                transform.rotation = glm::radians(rotation);

            ImGuiHelper::drawVec3Control("Scale", transform.scale);
        });

        drawComponent<CameraComponent>("Camera", entity, [](CameraComponent& camera) {
            ImGuiHelper::drawCheckbox("Primary", camera.primary);
            ImGuiHelper::drawCheckbox("Fixed Aspect Ratio", camera.fixedAspectRatio);

            constexpr std::array<const char*, 2> projectionTypeStrings = { "Perpective",
                                                                           "Orthographic" };
            ImGuiHelper::drawEnumPicker("Projection", camera.projectionType, projectionTypeStrings);

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
            }
        });

        drawComponent<SpriteRendererComponent>(
            "Sprite Renderer", entity, [](SpriteRendererComponent& sprite) {
                ImGuiHelper::drawColorEdit("Color", sprite.color); //
            });

        ImGui::PopStyleVar();
    }

    // this will accept a list of templates
    template <typename... ComponentType>
    static void drawAddComponentMenuItem(Entity entity)
    {
        if constexpr (sizeof...(ComponentType) == 1)
        {
            rttr::type type = rttr::type::get<ComponentType...>();
            rttr::variant prettyNameVar = type.get_metadata(ReflectMetaData::PrettyName);
            const char* name =
                prettyNameVar ? prettyNameVar.get_value<const char*>() : type.get_name().data();

            if (!entity.hasComponent<ComponentType...>() && ImGui::MenuItem(name))
            {
                entity.addComponent<ComponentType...>();
                ImGui::CloseCurrentPopup();
            }
        }
        else
            (drawAddComponentMenuItem<ComponentType>(entity), ...);
    }

    template <>
    void InspectorPanel::inspectItem<Entity>(Entity& entity)
    {
        IdentifierComponent& indentifier = entity.getComponent<IdentifierComponent>();
        ImGuiHelper::drawInputTextBox("##name", indentifier.name);

        ImGui::Separator();
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
            drawAddComponentMenuItem VR_COMPONENT_TEMPLATE_LIST(entity);
            ImGui::EndPopup();
        }
    }

} // namespace Varak
