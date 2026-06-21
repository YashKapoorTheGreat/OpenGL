#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "events.hpp"
#include "application.hpp"
#include "basicCube.hpp"

Game::Game(Application *app) :
    application(app),
    m_basic("res/shaders/basic.shader"),
    m_texture("res/images/container.jpg", 0, GL_RGB, GL_RGB),
    m_bag("res/models/bag/backpack.obj"),
    m_cubeFlat(verticesFlat, cubeIndicesFlat, { m_texture })
{
    float n = 0.1f;             // Near plane
    float f = 100.0f;           // Far plane
    float thetaFOV = 45.0f * 2; // Field of view in degrees

    m_camera = Camera(thetaFOV, (float)640 / (float)640, n, f);

    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_basic.Bind();
    m_basic.SetUniform1i("u_texture", 0);
    m_basic.SetUniform1i("u_skybox", 1);
}

Game::~Game()
{
}

void Game::Update(float delta)
{
    MoveCamera(delta);

    glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));

    m_basic.Bind();
    m_texture.Bind();
    m_basic.SetUniformMatrix4("u_model", modelMatrix);
    m_basic.SetUniformMatrix4("u_view", m_camera.GetView());
    m_basic.SetUniformMatrix4("u_projection", m_camera.GetProjection());
    m_cubeFlat.Draw(m_basic);


    //m_texture.Unbind();
    m_basic.SetUniformMatrix4("u_model", glm::translate(glm::mat4(1.0f), glm::vec3(3,0,0)));
    m_bag.Draw(m_basic);
}

void Game::MoveCamera(float delta)
{
    glm::vec3 camPos = m_camera.GetPosition();
    if (keyPressed & W_PRESSED)
        camPos += m_camera.GetForward() * m_camSpeed * delta;
    if (keyPressed & S_PRESSED)
        camPos -= m_camera.GetForward() * m_camSpeed * delta;
    if (keyPressed & A_PRESSED)
        camPos += glm::cross(m_camera.GetUp(), m_camera.GetForward()) * m_camSpeed * delta;
    if (keyPressed & D_PRESSED)
        camPos -= glm::cross(m_camera.GetUp(), m_camera.GetForward()) * m_camSpeed * delta;
    if (keyPressed & Q_PRESSED)
        camPos += m_camera.GetUp() * m_camSpeed * delta;
    if (keyPressed & E_PRESSED)
        camPos -= m_camera.GetUp() * m_camSpeed * delta;
    m_camera.SetPosition(camPos);

    if (keyPressed & LEFT_MOUSE_PRESSED)
    {
        application->DisableCursor();
        int dX = mouseX - m_lastMouseX;
        int dY = mouseY - m_lastMouseY;

        m_yaw += dX * m_mouseSensitivity * delta;
        m_pitch -= dY * m_mouseSensitivity * delta;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }
    else
        application->EnableCursor();

    glm::vec3 front = { cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
                        sin(glm::radians(m_pitch)),
                        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))};
    m_camera.SetForward(front);

    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;
}

void Game::UpdateViewport(int width, int height)
{
    m_camera.SetAspectRatio((float)width / (float)height);
}
