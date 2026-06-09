#include <GL/glew.h>

class ShaderProgram
{
private:
    unsigned int ID;

public:
    const char *vShaderSource;
    const char *fShaderSource;
    ShaderProgram(const char *shaderFile);
    ~ShaderProgram();

    void use();
};
