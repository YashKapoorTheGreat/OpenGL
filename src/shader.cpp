#include "shader.hpp"
#include <string>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(const char *shaderFile)
{
    // Load the code
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream shaderFileObject(shaderFile);

    if (!shaderFileObject.is_open())
    {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    std::string line;
    std::getline(shaderFileObject, line);
    while (!shaderFileObject.eof() && line.find("##shader") != std::string::npos)
    {
        if (line.find("##shader") != std::string::npos)
        {
            std::string shaderType = line.substr(9);
            if (shaderType == "vertex")
            {
                while (std::getline(shaderFileObject, line) && line.find("##shader") == std::string::npos)
                {
                    vertexCode += line + "\n";
                }
            }
            if (shaderType == "fragment")
            {
                while (std::getline(shaderFileObject, line) && line.find("##shader") == std::string::npos)
                {
                    fragmentCode += line + "\n";
                }
            }
        }
        else
        {
            std::cerr << "ERROR::SHADER::INVALID_SHADER_FILE_FORMAT" << std::endl;
        }
    }
    shaderFileObject.close();

    vShaderSource = vertexCode.c_str();
    fShaderSource = fragmentCode.c_str();

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
    glUseProgram(ID);
}
