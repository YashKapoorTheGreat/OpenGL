#include "shader.hpp"
#include "camera.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Update(float delta);
    void UpdateViewport(int width, int height);

private:
    ShaderProgram basic;
    Camera camera;
    float camSpeed = 5.0f;
    float mouseSensitivity = 70.0f;
    int lastMouseX, lastMouseY;
    float yaw = -90.0f;
    float pitch = 0.0f;

private:
    void moveCamera(float delta);
};
