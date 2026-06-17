#include <GLFW/glfw3.h>
#include "events.hpp"
#include <map>
#include <iostream>

// keyPressed is a global variable to track key states
unsigned char keyPressed = 0;
int mouseX = 0;
int mouseY = 0;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_REPEAT)
        return;

    unsigned char mask = 0;
    switch (key)
    {
    case GLFW_KEY_W:
        mask = W_PRESSED;
        break;
    case GLFW_KEY_A:
        mask = A_PRESSED;
        break;
    case GLFW_KEY_S:
        mask = S_PRESSED;
        break;
    case GLFW_KEY_D:
        mask = D_PRESSED;
        break;
    case GLFW_KEY_Q:
        mask = Q_PRESSED;
        break;
    case GLFW_KEY_E:
        mask = E_PRESSED;
        break;
    default:
        return; // Key is not bound, exit early
    }

    if (action == GLFW_PRESS)
    {
        keyPressed |= mask;
    }
    else if (action == GLFW_RELEASE)
    {
        keyPressed &= ~mask;
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    unsigned char mask = 0;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        mask = LEFT_MOUSE_PRESSED;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        mask = RIGHT_MOUSE_PRESSED;
        break;
    default:
        return; // Key is not bound, exit early
    }

    if (action == GLFW_PRESS)
        keyPressed |= mask;
    else if (action == GLFW_RELEASE)
        keyPressed &= ~mask;
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    mouseX = (int)xposIn;
    mouseY = (int)yposIn;
}
