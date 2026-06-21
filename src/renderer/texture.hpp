#pragma once

class Texture2D
{
public:
	Texture2D(const char* path, unsigned char texLevel, int internalFormat, unsigned int format);
	~Texture2D();
	void Bind();
	void Unbind();

private:
	int m_width, m_height, m_nrChannels;
	unsigned int m_id;
	unsigned char m_texLevel;
};
