#include "vrpch.h"

#include "varak/imgui/imgui_layer.h"

#include "scene_hierarchy_panel.h"

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

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity& entity)
    {
        IdentifierComponent& idComponent = entity.getComponent<IdentifierComponent>();

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= m_selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, idComponent.name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_selectedEntity = entity;
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

} // namespace Varak
