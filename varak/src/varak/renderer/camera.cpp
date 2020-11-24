#include "vrpch.h"

#include "varak/renderer/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    void Camera::setViewportSize(uint32_t width, uint32_t height)
    {
        m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        recalculateProjection();
    }

    void Camera::recalculateProjection()
    {
        if (m_projectionType == ProjectionType::Perpective)
        {
            m_projection = glm::perspective(m_perpectiveFOV, m_aspectRatio, m_perpectiveNear, m_perpectiveFar);
        }
        else
        {
            float orthoLeft = -m_orthographicSize * m_aspectRatio;
            float orthoRight = m_orthographicSize * m_aspectRatio;
            float orthoBottom = -m_orthographicSize;
            float orthoTop = m_orthographicSize;

            m_projection =
                glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_orthographicNear, m_orthographicFar);
        }
    }

} // namespace Varak
