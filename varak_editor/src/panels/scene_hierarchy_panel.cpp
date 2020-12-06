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

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
        {
            m_inspectorPanel->setSelected({});
        }

        ImGuiPopupFlags popupFlags = ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;
        if (ImGui::BeginPopupContextWindow(0, popupFlags))
        {
            if (ImGui::MenuItem("Create Empty"))
                m_scene->createEntity();

            ImGui::EndPopup();
        }

        ImGui::ShowDemoWindow();

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        std::string& name = entity.getComponent<IdentifierComponent>().name;

        if (m_isNameBeingEdited && m_inspectorPanel->getSelected() == entity)
        {
            ImVec2 size(ImGui::GetContentRegionAvail().x, 0.0f);
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll;

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
            if (ImGuiHelper::drawInputText(name, size, flags, (uint32_t)entity))
                m_isNameBeingEdited = false;
            ImGui::PopStyleVar();

            if (!ImGui::IsItemFocused())
                ImGui::SetKeyboardFocusHere(0);

            if (!ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                m_isNameBeingEdited = false;
        }
        else
        {
            ImGuiTreeNodeFlags treeNodeFlags =
                ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
            if (m_inspectorPanel->getSelected() == entity)
                treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
            bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();

            if (m_inspectorPanel->getSelected() == entity)
            {
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    m_isNameBeingEdited = true;
            }
            else
            {
                if (ImGui::IsItemClicked())
                    m_inspectorPanel->setSelected({ entity });
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Rename"))
                    m_isNameBeingEdited = true;

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
    }

} // namespace Varak
