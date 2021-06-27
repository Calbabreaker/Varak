#pragma once

#include "varak_app.h"
#include "varak_ecs.h"
#include "varak_imgui.h"

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
        std::shared_ptr<FrameBuffer> m_frameBuffer;

        std::shared_ptr<Scene> m_scene;
        Entity m_squareEntity;
        Entity m_cameraEntity;

        InspectorPanel m_inspectorPanel;
        SceneHierarchyPanel m_sceneHierarchyPanel;
        EditorCamera m_editorCamera;
        ImGuiLayer* m_imguiLayer;

        bool m_viewportFocused = false, m_viewportHovered = false;

        bool m_isPlaying = false;
    };

} // namespace Varak
