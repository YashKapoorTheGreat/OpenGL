#pragma once

class Game;
struct GLFWwindow;

class Application
{
public:
    Application(int width, int height, const char *title, int &errCode);
    ~Application();
    void Run();
    void EnableCursor();
    void DisableCursor();

private:
    int m_width, m_height;
    Game *game = nullptr;
    GLFWwindow *window = nullptr;

private:
    static void ResizeCallback(GLFWwindow *window, int width, int height);
};