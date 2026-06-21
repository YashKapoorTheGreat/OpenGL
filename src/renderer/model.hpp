#pragma once
#include "mesh.hpp"

struct aiMesh;
struct aiScene;

class Model
{
public:
	Model(const char *path);
	~Model();

	void Draw(ShaderProgram& shader);

private:
	std::vector<Mesh> meshes;
	Mesh processAIMesh(aiMesh* mesh, const aiScene* scene);
};
