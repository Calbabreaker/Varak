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
        
        Ref<FrameBuffer> m_frameBuffer;

        Scope<OrthographicCameraController> m_cameraController;
    };

} // namespace Varak
