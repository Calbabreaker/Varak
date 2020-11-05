#pragma once

#include "varak/events/event.h"
#include "varak/events/mouse_event.h"
#include "varak/renderer/orthographic_camera.h"

namespace Varak {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        void onUpdate();
        void onEvent(Event& event);

        bool onMouseScrolled(MouseScrolledEvent& event);

        OrthographicCamera& getCamera() { return m_camera; }

    private:
        void recaculateProjection();

    private:
        float m_aspectRatio;
        float m_zoomLevel = 1.0f;

        float m_cameraSpeed = 0.1f;
        float m_zoomSpeed = 0.25f;

        OrthographicCamera m_camera;
    };

} // namespace Varak