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

        virtual void setViewportSize(uint32_t width, uint32_t height);

        glm::mat4 getProjection() const;

    public:
        ProjectionType projectionType = ProjectionType::Orthographic;

        float perpectiveFOV = glm::radians(45.0f);
        float perpectiveNear = 0.01f, perpectiveFar = 1000.0f;

        float orthographicSize = 5.0f;
        float orthographicNear = -1.0f, orthographicFar = 1.0f;

    private:
        float m_aspectRatio = 0.0f;
    };

} // namespace Varak
