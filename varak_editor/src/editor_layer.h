#pragma once

#include "varak/ecs/editor_camera.h"
#include "varak/ecs/entity.h"
#include "varak/imgui/imgui_layer.h"
#include "varak/renderer/frame_buffer.h"

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
