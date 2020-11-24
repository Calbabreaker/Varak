#pragma once

#include "varak.h"

#include "panels/scene_hierarchy_panel.h"

namespace Varak {

    class EditorLayer : public Layer
    {
    public:
        void onAttach() override;
        void onDetach() override;

        void onUpdate(Timestep ts) override;
        void onImGuiRender() override;
        void onEvent(Event& event) override;

    private:
        Ref<Texture> m_vTexture;
        Ref<Texture> m_patternTexture;
        Ref<FrameBuffer> m_frameBuffer;

        Scope<CameraController> m_cameraController;

        Ref<Scene> m_scene;
        Entity m_squareEntity;
        Entity m_cameraEntity;

        SceneHierarchyPanel m_sceneHierarchyPanel;

        glm::vec2 m_viewportSize;
        bool m_viewportFocused = false, m_viewportHovered = false;
    };

} // namespace Varak
