#include "shader.hpp"
#include "assetManager.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

ShaderProgram::ShaderProgram(const char *shaderFile)
{
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
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(ID);
}

void ShaderProgram::Bind()
{
    glUseProgram(ID);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::setMVPUniforms(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &model)
{
    int u_model = glGetUniformLocation(ID, "u_model");
    if (u_model != -1)
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));

    int u_view = glGetUniformLocation(ID, "u_view");
    if (u_view != -1)
        glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));

    int u_projection = glGetUniformLocation(ID, "u_projection");
    if (u_projection != -1)
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
}
