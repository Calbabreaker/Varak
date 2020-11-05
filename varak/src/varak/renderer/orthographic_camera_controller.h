#pragma once

#include "varak/renderer/orthographic_camera.h"
#include "varak/events/event.h"

namespace Varak {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        void onUpdate();
        void onEvent(Event& event);

        OrthographicCamera& getCamera() { return m_camera; }
    private:
        float m_aspectRatio;
        float m_zoomLevel = 1.0f;
        float m_cameraSpeed = 0.1f;

        OrthographicCamera m_camera;
    };

} // namespace Varak