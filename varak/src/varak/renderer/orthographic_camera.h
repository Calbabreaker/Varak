#pragma once

#include <glm/glm.hpp>

namespace Varak {

    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top,
                           float znear = -1.0f, float zfar = 1.0f);

        void setProjection(float left, float right, float bottom, float top,
                           float znear = -1.0f, float zfar = 1.0f);

        void setPosition(const glm::vec3& position)
        {
            m_position = position;
            recalculateMatrices();
        };

        void setRotation(float rotation)
        {
            m_rotation = rotation;
            recalculateMatrices();
        }

        float getRotation() { return m_rotation; }
        const glm::vec3& getPosition() const { return m_position; }
        const glm::mat4& getViewProjection() const { return m_viewProjection; }
        const glm::mat4& getView() const { return m_view; }
        const glm::mat4& getProjection() const { return m_projection; }

    private:
        void recalculateMatrices();

    private:
        glm::mat4 m_projection;
        glm::mat4 m_viewProjection;
        glm::mat4 m_view;

        float m_rotation = 0.0f;
        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
    };

} // namespace Varak