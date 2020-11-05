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
        OrthographicCamera m_camera;

        float m_moveSpeed = 0.1f;
        float m_zoomSpeed = 0.25f;
    };

} // namespace Varak