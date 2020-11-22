#pragma once

#include <glm/glm.hpp>

namespace Varak {

    class Camera
    {
    public:
        enum class ProjectionType
        {
            Perpective,
            Orthographic
        };

    public:
        Camera() = default;

        void setViewportSize(uint32_t width, uint32_t height);

        const glm::mat4& getProjection() const { return m_projection; };

        // clang-format off
        void setOrthographicSize(float size) { m_orthographicSize = size; recalculateProjection(); }
        float getOrthographicSize() const { return m_orthographicSize; }

        void setProjectionType(ProjectionType type) { m_projectionType = type; recalculateProjection(); }
        ProjectionType getProjectionType() const { return m_projectionType; }
        // clang-format on

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
