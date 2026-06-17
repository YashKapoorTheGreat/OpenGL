#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.hpp"
#include "events.hpp"
#include "basicCube.hpp"
#include <iostream>

Game::Game() : basic("res/basic.shader")
{
    float n = 0.1f;             // Near plane
    float f = 100.0f;           // Far plane
    float thetaFOV = 45.0f * 2; // Field of view in degrees

    camera = Camera(thetaFOV, (float)640 / (float)640, n, f);
    basic.Bind();

    unsigned int VertexBufferID;
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 144 * sizeof(float), verticesFlat, GL_STATIC_DRAW);

    unsigned int ElementBufferID;
    glGenBuffers(1, &ElementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), cubeIndicesFlat, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

Game::~Game()
{
}

void Game::Update(float delta)
{
    moveCamera(delta);
    glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * 2, glm::vec3(0.0f, 1.0f, 0.0f));

    basic.Bind();
    basic.setMVPUniforms(camera.GetProjection(), camera.GetView(), modelMatrix);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Game::moveCamera(float delta)
{
    glm::vec3 camPos = camera.getPosition();
    if (keyPressed & W_PRESSED)
        camPos += camera.getForward() * camSpeed * delta;
    if (keyPressed & S_PRESSED)
        camPos -= camera.getForward() * camSpeed * delta;
    if (keyPressed & A_PRESSED)
        camPos += glm::cross(camera.getUp(), camera.getForward()) * camSpeed * delta;
    if (keyPressed & D_PRESSED)
        camPos -= glm::cross(camera.getUp(), camera.getForward()) * camSpeed * delta;
    if (keyPressed & Q_PRESSED)
        camPos += camera.getUp() * camSpeed * delta;
    if (keyPressed & E_PRESSED)
        camPos -= camera.getUp() * camSpeed * delta;
    camera.setPosition(camPos);

    if (keyPressed & LEFT_MOUSE_PRESSED)
    {
        int dX = mouseX - lastMouseX;
        int dY = mouseY - lastMouseY;

        yaw += dX * mouseSensitivity * delta;
        pitch -= dY * mouseSensitivity * delta;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera.setForward(glm::normalize(front));

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void Game::UpdateViewport(int width, int height)
{
    camera.setAspectRatio((float)width / (float)height);
}
