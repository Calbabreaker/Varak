#pragma once

#include "varak/app/timestep.h"
#include "varak/event/event.h"
#include "varak/event/mouse_event.h"
#include "varak/math/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Varak {

    class EditorCamera : public Camera
    {
    public:
        EditorCamera();

        void onUpdate(Timestep ts);
        void onEvent(Event& event);

        void setViewportSize(uint32_t width, uint32_t height) override;

        glm::mat4 getViewProjection() const;

        glm::vec3 getPosition() const { return m_focalPoint - getForwardDirection() * m_distance; }
        glm::quat getOrientation() const { return glm::quat(glm::vec3(m_yaw, m_pitch, 0.0f)); }

        glm::vec3 getUpDirection() const
        {
            return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        glm::vec3 getRightDirection() const
        {
            return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        glm::vec3 getForwardDirection() const
        {
            return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
        }

    private:
        void calcMousePan(const glm::vec2& offset);
        void calcMouseRotate(const glm::vec2& offset);
        void calcMouseZoom(float offset);

        bool onMouseMoved(MouseMovedEvent& event);
        bool onMouseScrolled(MouseScrolledEvent& event);

    private:
        float m_rotationSpeed = 0.8f;
        glm::vec2 m_panSpeed = { 0.0f, 0.0f };

        float m_mouseMoveOffsetMult = 0.01f;
        float m_mouseScrollOffsetMult = 0.1f;

        float m_distance = 10.0f;
        glm::vec3 m_focalPoint = { 0.0f, 0.0f, 0.0f };
        float m_yaw = 0.0f;
        float m_pitch = 0.0f;
    };

}; // namespace Varak
