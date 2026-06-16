#include "shader.hpp"
#include "assetManager.hpp"
#include "GLFW/glfw3.h"
#include <cmath>
#include <iostream>

ShaderProgram::ShaderProgram(const char *shaderFile)
{
    // Load the code
    std::pair<std::string, std::string> shaderSources = AssetManager::loadShader(shaderFile);

    vShaderSource = shaderSources.first.c_str();
    fShaderSource = shaderSources.second.c_str();

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

void ShaderProgram::use()
{
    float n = 0.1f;         // Near plane
    float f = 100.0f;       // Far plane
    float thetaFOV = 45.0f; // Field of view in degrees

    float theta = (float)glfwGetTime() * 2;
    float model[16] = {
        cosf(theta), 0.0, sinf(theta), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sinf(theta), 0.0, cosf(theta), 0.0,
        0.0, 0.0, 0.0, 1.0};

    float view[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, -1.0, -2.5, 1.0};

    float projection[16] = {
        tanf(thetaFOV * 3.14159f / 180.0f), 0.0, 0.0, 0.0,
        0.0, tanf(thetaFOV * 3.14159f / 180.0f), 0.0, 0.0,
        0.0, 0.0, (f + n) / (n - f), -1.0,
        0.0, 0.0, 2 * f * n / (n - f), 0.0};

    glUseProgram(ID);

    int u_model = glGetUniformLocation(ID, "u_model");
    if (u_model != -1)
        glUniformMatrix4fv(u_model, 1, GL_FALSE, &model[0]);

    int u_view = glGetUniformLocation(ID, "u_view");
    if (u_view != -1)
        glUniformMatrix4fv(u_view, 1, GL_FALSE, &view[0]);

    int u_projection = glGetUniformLocation(ID, "u_projection");
    if (u_projection != -1)
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0]);
}
