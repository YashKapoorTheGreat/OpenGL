#pragma once
#include "utils.hpp"
#include <GLFW/glfw3.h>

class Renderer
{
private:
    GLFWwindow *window;

public:
    int RendererInit(int width, int height, const char *title);
    bool IsRunning()
    {
        return !glfwWindowShouldClose(window);
    }
    void Shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    void Update();
};