#include "camera.hpp"
#include <glm/ext.hpp>

Camera::Camera(float FOV, float aspectRatio, float nearClip, float farClip)
    : m_FOV(FOV), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
{
    m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::UpdateView()
{
    m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::UpdateProjection()
{
    m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
}

void Camera::setPosition(glm::vec3 position)
{
    m_Position = position;
    UpdateView();
}

void Camera::setForward(glm::vec3 forward)
{
    m_Forward = forward;
    UpdateView();
}

void Camera::setUp(glm::vec3 up)
{
    m_Up = up;
    UpdateView();
}

void Camera::setAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    UpdateProjection();
}

void Camera::setFOV(float FOV)
{
    m_FOV = FOV;
    UpdateProjection();
}
