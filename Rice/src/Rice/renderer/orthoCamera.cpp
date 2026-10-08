//
// Created by luantsp on 04/10/2026.
//
#include "orthoCamera.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Rice {
    OrthoCamera::OrthoCamera(const float left, const float right, const float bottom, const float top) {
        // Initialize projection matrix
        m_Projection = glm::ortho(left, right, bottom, top);

        // Initialize positon and angle of rotation
        m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
        m_Rotation = 0.0f;

        // Initialize view
        const glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(
                glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f)
            );

        m_View = glm::inverse(transform);
    }

    void OrthoCamera::updateView() {
        const glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(
                glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f)
            );

        m_View = glm::inverse(transform);
    }
}
