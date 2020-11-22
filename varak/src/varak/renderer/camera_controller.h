#pragma once

#include "varak/core/timestep.h"
#include "varak/events/event.h"
#include "varak/events/mouse_event.h"
#include "varak/events/window_event.h"
#include "varak/renderer/camera.h"

namespace Varak {

    class CameraController
    {
    public:
        CameraController(uint32_t width, uint32_t height);

        void onUpdate(Timestep ts);
        void onEvent(Event& event);

        void setZoomLevel(float zoomLevel);
        glm::mat4 getTransform();

        void onResize(uint32_t width, uint32_t height);

        bool onMouseScrolled(MouseScrolledEvent& event);

        Camera& getCamera() { return m_camera; }

    private:
        float m_zoomLevel = 1.0f;
        Camera m_camera;

        float m_moveSpeed = 5.0f;
        float m_zoomSpeed = 0.10f;
        float m_realZoomSpeed;
        float m_minZoomLevel = 0.25f;
        float m_maxZoomLevel = 50.0f;
        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    };

} // namespace Varak
