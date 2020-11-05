#include "varak/renderer/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    OrthographicCamera::OrthographicCamera(float left, float right,
                                           float bottom, float top, float znear,
                                           float zfar)
        : m_projection(glm::ortho(left, right, bottom, top, znear, zfar)),
          m_view(1.0f)
    {
        m_viewProjection = m_projection * m_view;
    }

    void OrthographicCamera::setProjection(float left, float right,
                                           float bottom, float top, float znear,
                                           float zfar)
    {
        m_projection = glm::ortho(left, right, bottom, top, znear, zfar);
        m_viewProjection = m_projection * m_view;
    }

    void OrthographicCamera::recalculateMatrices()
    {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), m_position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation),
                        glm::vec3(0.0f, 0.0f, 1.0f));

        m_view = glm::inverse(transform);
        m_viewProjection = m_projection * m_view;
    }

} // namespace Varak