#include "varak_imgui.h"

#include "scene_hierarchy_panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Varak {

    SceneHierarchyPanel::SceneHierarchyPanel(InspectorPanel* panel) : m_inspectorPanel(panel) {}

    void SceneHierarchyPanel::setScene(const std::shared_ptr<Scene>& scene)
    {
        m_scene = scene; //
    }

    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 1.0f));

        ImGui::Begin("Hierarchy");

        ImGui::PopStyleVar();

        m_scene->m_registry.each([&](entt::entity entityID) {
            Entity entity(entityID, m_scene.get());
            drawEntityNode(entity);
        });

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
            m_inspectorPanel->clearSelected();

        ImGuiPopupFlags popupFlags =
            ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;
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
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 2.0f));

        std::string& name = entity.getComponent<IdentifierComponent>().name;

        if (m_nameBeingEdited && m_inspectorPanel->matchesSelected(entity))
        {
            ImGuiInputTextFlags inputFlags =
                ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll;
            if (ImGuiHelper::drawInputTextBox("##name", name, inputFlags))
                m_nameBeingEdited = false;
            ImGui::PopStyleVar(2);

            if (!ImGui::IsItemFocused())
                ImGui::SetKeyboardFocusHere(0);

            if (!ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                m_nameBeingEdited = false;
        }
        else
        {
            ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
                                               ImGuiTreeNodeFlags_SpanAvailWidth |
                                               ImGuiTreeNodeFlags_FramePadding;
            if (m_inspectorPanel->matchesSelected(entity))
                treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

            uint64_t entityID = static_cast<uint64_t>(entity.getID());
            bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(entityID), treeNodeFlags, "%s",
                                            name.c_str());

            ImGui::PopStyleVar(2);

            if (m_inspectorPanel->matchesSelected(entity))
            {
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    m_nameBeingEdited = true;
            }
            else
            {
                if (ImGui::IsItemClicked())
                    m_inspectorPanel->setSelected<Entity>(entity);
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Rename"))
                    m_nameBeingEdited = true;

                if (ImGui::MenuItem("Destroy Entity"))
                {
                    if (m_inspectorPanel->matchesSelected(entity))
                        m_inspectorPanel->clearSelected();

                    m_scene->destroyEntity(entity);
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
