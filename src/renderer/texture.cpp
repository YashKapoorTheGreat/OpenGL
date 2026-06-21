#include "texture.hpp"
#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>

Texture2D::Texture2D(const char* path, unsigned char texLevel, int internalFormat, unsigned int format) : m_texLevel(texLevel)
{
    //std::cout << "LOADING TEXTURE: " << path << std::endl;
	unsigned char* data = stbi_load(path, &m_width, &m_height, &m_nrChannels, 0);
	glGenTextures(1, &m_id);
    Bind();

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    //std::cout << "LOADED TEXTURE: " << path << std::endl;
}

Texture2D::~Texture2D()
{
}

void Texture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0 + m_texLevel);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::Unbind()
{
    glActiveTexture(GL_TEXTURE0 + m_texLevel);
    glBindTexture(GL_TEXTURE_2D, 0);
}
