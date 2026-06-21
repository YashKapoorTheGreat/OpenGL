#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>

class ShaderProgram
{
public:
    ShaderProgram(const char *shaderFile);
    ~ShaderProgram();

    void Bind() const;
    void Unbind();
    void SetUniform1i(const char *name, int num);
    void SetUniform4f(const char *name, const glm::vec4 &vector);
    void SetUniformMatrix4(const char *name, const glm::mat4 &matrix);

private:
    unsigned int ID = 0;
    std::map<const char *, int> UniformCache;

private:
    int GetUniformLocation(const char *name);
};
