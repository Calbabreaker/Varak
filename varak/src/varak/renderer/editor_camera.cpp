#include "vrpch.h"

#include "varak/core/input.h"
#include "varak/renderer/editor_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    EditorCamera::EditorCamera()
    {
        setProjectionType(Camera::ProjectionType::Perpective);
        updateViewProjection();
    }

    void EditorCamera::onUpdate(Timestep ts) {}

    void EditorCamera::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseMovedEvent>(VR_BIND_FUNC(EditorCamera::onMouseMoved));
        dispatcher.dispatch<MouseScrolledEvent>(VR_BIND_FUNC(EditorCamera::onMouseScrolled));
    }

    void EditorCamera::setViewportSize(uint32_t width, uint32_t height)
    {
        // calculate the pan speed
        float x = glm::min(width / 1000.0f, 2.4f);
        float xFactor = 0.0366f * glm::pow(x, 2.0f) - 0.1778f * x + 0.3021f;

        float y = glm::min(height / 1000.0f, 2.4f);
        float yFactor = 0.0366f * glm::pow(y, 2.0f) - 0.1778f * y + 0.3021f;
        m_panSpeed = { xFactor, yFactor };

        Camera::setViewportSize(width, height);
        updateViewProjection();
    }

    void EditorCamera::updateViewProjection()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), getPosition()) * glm::toMat4(getOrientation());
        glm::mat4 view = glm::inverse(transform);

        m_viewProjection = getProjection() * view;
    }

    void EditorCamera::calcMousePan(const glm::vec2& offset)
    {
        m_focalPoint += -getRightDirection() * offset.x * m_panSpeed.x * m_distance;
        m_focalPoint += getUpDirection() * offset.y * m_panSpeed.y * m_distance;
        updateViewProjection();
    }

    void EditorCamera::calcMouseRotate(const glm::vec2& offset)
    {
        float yawSign = glm::sign(getUpDirection().y);
        m_yaw -= yawSign * offset.y * m_rotationSpeed;
        m_pitch -= offset.x * m_rotationSpeed;
        updateViewProjection();
    }

    void EditorCamera::calcMouseZoom(float offset)
    {
        float zoomSpeed = glm::pow(glm::max(m_distance * 0.2f, 0.0f), 2.0f);
        zoomSpeed = glm::min(zoomSpeed, 100.0f);

        m_distance -= offset * zoomSpeed;
        if (m_distance < 1.0f)
        {
            m_focalPoint += getForwardDirection();
            m_distance = 1.0f;
        }

        updateViewProjection();
    }

    bool EditorCamera::onMouseMoved(MouseMovedEvent& event)
    {
        glm::vec2 offset = event.getOffset() * m_mouseMoveOffsetMult;
        if (Input::isMouseButtonPressed(MouseCode::ButtonMiddle))
        {
            if (Input::isKeyPressed(KeyCode::LeftShift))
                calcMousePan(offset);
            else
                calcMouseRotate(offset);
        }

        return false;
    }

    bool EditorCamera::onMouseScrolled(MouseScrolledEvent& event)
    {
        float yOffset = event.getOffset().y * m_mouseScrollOffsetMult;
        calcMouseZoom(yOffset);
        return false;
    }

} // namespace Varak
