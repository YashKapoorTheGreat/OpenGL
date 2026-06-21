#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.hpp"
#include "../assetManager.hpp"

ShaderProgram::ShaderProgram(const char *shaderFile)
{
    //std::cout << "LOADING SHADER: " << shaderFile << std::endl;
    // Load the code
    std::pair<std::string, std::string> shaderSources = AssetManager::loadShader(shaderFile);

    const char *vShaderSource = shaderSources.first.c_str();
    const char *fShaderSource = shaderSources.second.c_str();

    // Compile the code
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link the shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //std::cout << "LOADED SHADER: " << shaderFile << std::endl;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(ID);
}

void ShaderProgram::Bind() const
{
    glUseProgram(ID);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::SetUniform4f(const char *name, const glm::vec4 &vector)
{
    int u_float = GetUniformLocation(name);
    if (u_float != -1)
        glUniform4f(u_float, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::SetUniform1i(const char* name, int num)
{
    int u_int = GetUniformLocation(name);
    if (u_int != -1)
        glUniform1i(u_int, num);
}

void ShaderProgram::SetUniformMatrix4(const char* name, const glm::mat4& matrix)
{
    int u_matrix = GetUniformLocation(name);
    if (u_matrix != -1)
        glUniformMatrix4fv(u_matrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

int ShaderProgram::GetUniformLocation(const char *name)
{
    if (UniformCache.find(name) != UniformCache.end())
        return UniformCache[name];
    UniformCache[name] = glGetUniformLocation(ID, name);
    return UniformCache[name];
}
