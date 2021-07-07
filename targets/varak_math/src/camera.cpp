#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    void Camera::setViewportSize(uint32_t width, uint32_t height)
    {
        m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }

    glm::mat4 Camera::getProjection() const
    {
        switch (projectionType)
        {
        case ProjectionType::Perpective:
        {
            return glm::perspective(perpectiveFOV, m_aspectRatio, perpectiveNear, perpectiveFar);
        }

        case ProjectionType::Orthographic:
        {
            float orthoLeft = -orthographicSize * m_aspectRatio;
            float orthoRight = orthographicSize * m_aspectRatio;
            float orthoBottom = -orthographicSize;
            float orthoTop = orthographicSize;
            return glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthographicNear,
                              orthographicFar);
        }

        default: break;
        }

        return glm::mat4();
    }

} // namespace Varak
