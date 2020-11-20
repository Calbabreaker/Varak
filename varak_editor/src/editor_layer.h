#pragma once

#include <varak.h>

namespace Varak {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void onAttach() override;
        void onDetach() override;

        void onUpdate(Timestep ts) override;
        void onImGuiRender() override;
        void onEvent(Event& event) override;

    private:
        Ref<Texture> m_vTexture;
        Ref<Texture> m_patternTexture;

        Scope<OrthographicCameraController> m_cameraController;

        glm::vec4 m_squareColor = { 0.0f, 0.4f, 0.2f, 1.0f };
    };

} // namespace Varak
