#include "vrpch.h"

#include "varak/renderer/camera_controller.h"

#include "varak/core/input.h"
#include "varak/core/key_codes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    CameraController::CameraController(uint32_t width, uint32_t height)
    {
        m_camera.setViewportSize(width, height);
        setZoomLevel(m_zoomLevel);
    }

    void CameraController::onUpdate(Timestep ts)
    {
        VR_PROFILE_FUNCTION();

        glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
        if (Input::isKeyPressed(KeyCode::A))
            velocity.x -= 1.0f;
        if (Input::isKeyPressed(KeyCode::D))
            velocity.x += 1.0f;

        if (Input::isKeyPressed(KeyCode::S))
            velocity.y -= 1.0f;
        if (Input::isKeyPressed(KeyCode::W))
            velocity.y += 1.0f;

        if (glm::length(velocity) != 0)
            velocity = glm::normalize(velocity) * m_moveSpeed * ts.getSeconds();

        m_position += velocity;
    }

    void CameraController::onEvent(Event& event)
    {
        VR_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(VR_BIND_EVENT_FUNC(CameraController::onMouseScrolled));
    }

    void CameraController::setZoomLevel(float zoomLevel)
    {
        VR_PROFILE_FUNCTION();

        zoomLevel = glm::clamp(zoomLevel, m_minZoomLevel, m_maxZoomLevel);
        m_zoomLevel = zoomLevel;
        m_moveSpeed = m_zoomLevel;
        m_realZoomSpeed = zoomLevel * m_zoomSpeed;
        m_camera.setOrthographicSize(m_zoomLevel);
    }

    glm::mat4 CameraController::getTransform()
    {
        return glm::translate(glm::mat4(1.0f), m_position); //
    }

    void CameraController::onResize(uint32_t width, uint32_t height)
    {
        m_camera.setViewportSize(width, height); //
    }

    bool CameraController::onMouseScrolled(MouseScrolledEvent& event)
    {
        VR_PROFILE_FUNCTION();

        float zoomLevel = m_zoomLevel - event.getYOffset() * m_realZoomSpeed;
        setZoomLevel(zoomLevel);
        return false;
    }

} // namespace Varak
