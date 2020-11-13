#pragma once

#include "varak/core/timestep.h"
#include "varak/events/event.h"
#include "varak/events/mouse_event.h"
#include "varak/events/window_event.h"
#include "varak/renderer/orthographic_camera.h"

namespace Varak {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        void onUpdate(Timestep ts);
        void onEvent(Event& event);

        float getZoomLevel() const {return m_zoomLevel; };
        void setZoomLevel(float zoomLevel);

        bool onMouseScrolled(MouseScrolledEvent& event);
        bool onWindowResized(WindowResizedEvent& event);

        OrthographicCamera& getCamera() { return m_camera; }

    private:
        void recaculateProjection();

    private:
        float m_aspectRatio;
        float m_zoomLevel = 1.0f;
        OrthographicCamera m_camera;

        float m_moveSpeed = 5.0f;
        float m_zoomSpeed = 0.10f;
        float m_realZoomSpeed = m_zoomLevel * m_zoomSpeed;
        float m_minZoomLevel = 0.25f;
        float m_maxZoomLevel = 50.0f;
    };

} // namespace Varak
