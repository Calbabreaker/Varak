#include "vrpch.h"

#include "varak/imgui/imgui_helper.h"
#include "varak/imgui/imgui_layer.h"

#include "scene_hierarchy_panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    SceneHierarchyPanel::SceneHierarchyPanel(InspectorPanel* panel) : m_inspectorPanel(panel) {}

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
            m_inspectorPanel->setSelected({});

        ImGuiPopupFlags popupFlags = ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;
        if (ImGui::BeginPopupContextWindow(0, popupFlags))
        {
            if (ImGui::MenuItem("Create Empty"))
                m_scene->createEntity();

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& component = entity.getComponent<IdentifierComponent>();

        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        treeNodeFlags |= m_inspectorPanel->getSelected() == entity ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeNodeFlags, component.name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_inspectorPanel->setSelected({entity});
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Destroy Entity"))
            {
                m_scene->destroyEntity(entity);
                if (entity == m_inspectorPanel->getSelected())
                    m_inspectorPanel->setSelected({});
            }

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

} // namespace Varak
