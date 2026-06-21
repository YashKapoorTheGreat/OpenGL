#pragma once
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"
#include "renderer/mesh.hpp"
#include "renderer/model.hpp"
#include "camera.hpp"

class Application;

class Game
{
public:
    Game(Application *app);
    ~Game();
    void Update(float delta);
    void UpdateViewport(int width, int height);

private:
    Application *application = nullptr; // Refactor

private:
    ShaderProgram m_basic;
    Camera m_camera;
    Texture2D m_texture;
    Mesh m_cubeFlat;
    Model m_bag;

    float m_camSpeed = 5.0f;
    float m_mouseSensitivity = 70.0f;
    int m_lastMouseX, m_lastMouseY;
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;

private:
    void MoveCamera(float delta);
};
