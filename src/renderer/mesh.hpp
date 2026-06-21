#pragma once
#include <vector>
#include "texture.hpp"
#include "shader.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures);
	~Mesh();

    void Draw(ShaderProgram &shader);

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture2D> m_textures;

private:
    unsigned int m_VAO, m_VBO, m_EBO;
};
