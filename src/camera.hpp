#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    Camera() = default;
    Camera(float FOV, float aspectRatio, float nearClip, float farClip);

    const glm::mat4 &GetProjection() const { return m_Projection; }
    const glm::mat4 &GetView() const { return m_View; }

    void setPosition(glm::vec3 position);
    void setForward(glm::vec3 forward);
    void setUp(glm::vec3 up);
    void setAspectRatio(float aspectRatio);
    void setFOV(float FOV);

    inline glm::vec3 getPosition()
    {
        return m_Position;
    }
    inline glm::vec3 getForward()
    {
        return m_Forward;
    }
    inline glm::vec3 getUp()
    {
        return m_Up;
    }
    inline float getAspectRatio()
    {
        return m_AspectRatio;
    }
    inline float getFOV()
    {
        return m_FOV;
    }

private:
    glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    float m_FOV = 45.0f * 2;
    float m_AspectRatio = 1;
    float m_NearClip = 0.1f;
    float m_FarClip = 1000.0f;

private:
    glm::mat4 m_Projection = glm::mat4(1.0f);
    glm::mat4 m_View = glm::mat4(1.0f);
    void UpdateView();
    void UpdateProjection();
};