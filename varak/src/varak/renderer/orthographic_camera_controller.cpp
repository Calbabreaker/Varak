#include "varak/renderer/orthographic_camera_controller.h"

#include "varak/core/input.h"
#include "varak/core/key_codes.h"

namespace Varak {

    OrthographicCameraController::OrthographicCameraController(
        float aspectRatio)
        : m_aspectRatio(aspectRatio),
          m_camera(-m_zoomLevel * m_aspectRatio, m_zoomLevel * m_aspectRatio,
                   -m_zoomLevel, m_zoomLevel)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        glm::vec3 velocity = {0.0f, 0.0f, 0.0f};
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

        m_camera.setPosition(m_camera.getPosition() + velocity);
    }

    void OrthographicCameraController::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(
            VR_BIND_EVENT_FUNC(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizedEvent>(
            VR_BIND_EVENT_FUNC(OrthographicCameraController::onWindowResized));
    }

    void OrthographicCameraController::setZoomLevel(float zoomLevel)
    {
        m_zoomLevel = zoomLevel;
        m_moveSpeed = m_zoomLevel;
        recaculateProjection();
    }

    bool OrthographicCameraController::onMouseScrolled(
        MouseScrolledEvent& event)
    {
        float zoomLevel = m_zoomLevel - event.getYOffset() * m_realZoomSpeed;
        zoomLevel = glm::clamp(zoomLevel, m_minZoomLevel, m_maxZoomLevel);
        m_realZoomSpeed = zoomLevel * m_zoomSpeed;
        setZoomLevel(zoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResized(
        WindowResizedEvent& event)
    {
        m_aspectRatio = static_cast<float>(event.getWidth()) /
                        static_cast<float>(event.getHeight());
        recaculateProjection();
        return false;
    }

    void OrthographicCameraController::recaculateProjection()
    {
        m_camera.setProjection(-m_zoomLevel * m_aspectRatio,
                               m_zoomLevel * m_aspectRatio, -m_zoomLevel,
                               m_zoomLevel);
    }

} // namespace Varak
