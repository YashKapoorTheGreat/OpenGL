#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "application.hpp"
#include "game.hpp"
#include "utils.hpp"
#include "events.hpp"
#include <chrono>
#include <iostream>
#include <bitset>
#include <stb_image.h>

static void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    DEBUG_BREAK();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

void Application::ResizeCallback(GLFWwindow *window, int width, int height)
{
    Application *app = (Application *)glfwGetWindowUserPointer(window);
    app->m_height = height;
    app->m_width = width;
    app->game->UpdateViewport(width, height);
    glViewport(0, 0, width, height);
}

Application::Application(int width, int height, const char *title, int &errCode)
{
    m_width = width;
    m_height = height;

    if (!glfwInit())
    {
        errCode = -1;
        return;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        errCode = -1;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        errCode = -1;
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(ErrorCallback, NULL);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, ResizeCallback);

    stbi_set_flip_vertically_on_load(true);

    game = new Game(this);

    errCode = 0;
}

void Application::Run()
{
    long long deltaMs = 0;
    while (!glfwWindowShouldClose(window))
    {
        auto start = std::chrono::steady_clock::now();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game->Update(((float)deltaMs) * 0.000001f);
        glfwSwapBuffers(window);
        glfwPollEvents();
        auto end = std::chrono::steady_clock::now();
        auto delta = end - start;
        deltaMs = std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
        std::cout << "Delta time: " << deltaMs << " FPS: " << 1000000.0f / (float)deltaMs << std::endl;
    }
}

void Application::EnableCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::DisableCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Application::~Application()
{
    delete game;
    glfwDestroyWindow(window);
    glfwTerminate();
}
