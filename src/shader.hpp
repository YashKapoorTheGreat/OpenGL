#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ShaderProgram
{
private:
    unsigned int ID = 0;

public:
    ShaderProgram(const char *shaderFile);
    ~ShaderProgram();

    void Bind();
    void Unbind();
    void setMVPUniforms(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &model);
};
