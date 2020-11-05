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

    void OrthographicCameraController::onUpdate()
    {
        glm::vec3 velocity = {0.0f, 0.0f, 0.0f};
        if (Input::isKeyPressed(Key::A))
            velocity.x -= 1;
        if (Input::isKeyPressed(Key::D))
            velocity.x += 1;

        if (Input::isKeyPressed(Key::S))
            velocity.y -= 1;
        if (Input::isKeyPressed(Key::W))
            velocity.y += 1;

        if (glm::length(velocity) != 0)
            velocity = glm::normalize(velocity) * m_cameraSpeed;

        m_camera.setPosition(m_camera.getPosition() + velocity);
    }

    void OrthographicCameraController::onEvent(Event& event) {}

} // namespace Varak