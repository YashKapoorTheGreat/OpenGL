#include "assetManager.hpp"
#include <fstream>
#include <iostream>

std::pair<std::string, std::string> AssetManager::loadShader(const char *shaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream shaderFileObject(shaderFile);

    if (!shaderFileObject.is_open())
    {
        std::cerr << "Error: Could not open the file." << std::endl;
        return {"", ""};
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
    return {vertexCode, fragmentCode};
}
