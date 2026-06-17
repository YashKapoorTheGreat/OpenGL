#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.hpp"

class Application
{
public:
    Application(int width, int height, const char *title, int &errCode);
    ~Application();
    void Run();
    void Shutdown();

private:
    int m_width, m_height;
    Game *game = nullptr;
    GLFWwindow *window;

private:
    inline bool IsRunning()
    {
        return !glfwWindowShouldClose(window);
    }
};