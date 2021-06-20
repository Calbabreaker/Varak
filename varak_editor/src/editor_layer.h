#pragma once

#include "varak_app.h"
#include "varak_imgui.h"
#include "varak_scene.h"

#include "panels/inspector_panel/inspector_panel.h"
#include "panels/scene_hierarchy_panel.h"

namespace Varak {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer(ImGuiLayer* imguiLayer);

        void onAttach() override;
        void onDetach() override;

        void onUpdate(Timestep ts) override;
        void onRender() override;
        void onEvent(Event& event) override;

    private:
        Ref<FrameBuffer> m_frameBuffer;

        Ref<Scene> m_scene;
        Entity m_squareEntity;
        Entity m_cameraEntity;

        InspectorPanel m_inspectorPanel;
        SceneHierarchyPanel m_sceneHierarchyPanel;
        EditorCamera m_editorCamera;
        ImGuiLayer* m_imguiLayer;

        glm::vec2 m_viewportSize;
        bool m_viewportFocused = false, m_viewportHovered = false;

        bool m_isPlaying = false;
    };

} // namespace Varak
