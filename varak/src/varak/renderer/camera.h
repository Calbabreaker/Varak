#pragma once

#include <glm/glm.hpp>

namespace Varak {

    class Camera
    {
    public:
        enum class ProjectionType
        {
            Perpective = 0,
            Orthographic = 1
        };

    public:
        Camera() = default;

        void setViewportSize(uint32_t width, uint32_t height);

        const glm::mat4& getProjection() const { return m_projection; };

        // clang-format off
        void setPerpectiveFOV(float fov) {m_perpectiveFOV = fov; recalculateProjection(); }
        void setPerpectiveNearClip(float nearClip) { m_perpectiveNear = nearClip; recalculateProjection(); }
        void setPerpectiveFarClip(float farClip) { m_perpectiveFar = farClip; recalculateProjection(); }

        void setOrthographicSize(float size) { m_orthographicSize = size; recalculateProjection(); }
        void setOrthographicNearClip(float nearClip) { m_orthographicNear = nearClip; recalculateProjection(); }
        void setOrthographicFarClip(float farClip) { m_orthographicFar = farClip; recalculateProjection(); }

        void setProjectionType(ProjectionType type) { m_projectionType = type; recalculateProjection(); }
        // clang-format on

        float getPerpectiveFOV() const { return m_perpectiveFOV; }
        float getPerpectiveNearClip() const { return m_perpectiveNear; }
        float getPerpectiveFarClip() const { return m_perpectiveFar; }

        float getOrthographicSize() const { return m_orthographicSize; }
        float getOrthographicNearClip() const { return m_orthographicNear; }
        float getOrthographicFarClip() const { return m_orthographicFar; }

        ProjectionType getProjectionType() const { return m_projectionType; }

    private:
        void recalculateProjection();

    private:
        glm::mat4 m_projection = glm::mat4(1.0f);
        ProjectionType m_projectionType = ProjectionType::Orthographic;

        float m_perpectiveFOV = glm::radians(45.0f);
        float m_perpectiveNear = 0.01f, m_perpectiveFar = 1000.0f;

        float m_orthographicSize = 5.0f;
        float m_orthographicNear = -1.0f, m_orthographicFar = 1.0f;

        float m_aspectRatio = 0.0f;
    };

} // namespace Varak
