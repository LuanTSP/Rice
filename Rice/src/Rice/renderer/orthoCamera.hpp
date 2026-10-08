#pragma once

#include <glm/glm.hpp>

namespace Rice {
    class OrthoCamera {
    public:
        OrthoCamera(const float left, const float right, const float bottom, const float top);
        
        void        SetPosition(const glm::vec3& position) { m_Position = position; }
        void        SetRotation(const float rotation)      { m_Rotation = rotation; }
        glm::vec3   GetPosition()   const { return m_Position; }
        float       GetRotation()   const { return m_Rotation; }
        glm::mat4   GetView()       const { return m_View; }
        glm::mat4   GetProj()       const { return m_Projection; }
        void        updateView();
    private:
        glm::vec3 m_Position;
        float m_Rotation;
        glm::mat4 m_Projection;
        glm::mat4 m_View;
    };
}


