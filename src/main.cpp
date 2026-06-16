#include "renderer.hpp"
#include "shader.hpp"
#include "basicCube.hpp"

int main(void)
{
    Renderer renderer;
    int success = renderer.RendererInit(640, 640, "Hello There!");

    if (success != 0)
        return success;

    ShaderProgram basic("res/basic.shader");
    basic.use();

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

    while (renderer.IsRunning())
    {
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        basic.use();
        renderer.Update();
    }

    renderer.Shutdown();

    return 0;
}