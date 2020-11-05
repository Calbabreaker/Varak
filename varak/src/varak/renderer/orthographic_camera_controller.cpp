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
        if (Input::isKeyPressed(Key::A))
            velocity.x -= 1.0f;
        if (Input::isKeyPressed(Key::D))
            velocity.x += 1.0f;

        if (Input::isKeyPressed(Key::S))
            velocity.y -= 1.0f;
        if (Input::isKeyPressed(Key::W))
            velocity.y += 1.0f;

        if (glm::length(velocity) != 0)
            velocity = glm::normalize(velocity) * m_moveSpeed * ts.getSeconds();

        m_camera.setPosition(m_camera.getPosition() + velocity);

        m_moveSpeed = m_zoomLevel;
    }

    void OrthographicCameraController::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(
            VR_BIND_EVENT_FUNC(OrthographicCameraController::onMouseScrolled));
    }

    bool OrthographicCameraController::onMouseScrolled(
        MouseScrolledEvent& event)
    {
        m_zoomLevel -= event.getYOfset() * m_zoomSpeed;
        m_zoomLevel = std::max(m_zoomLevel, 0.25f);
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