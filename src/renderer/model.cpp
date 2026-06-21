#include "model.hpp"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const char* path)
{
	//std::cout << "LOADING MODEL: " << path << std::endl;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	std::vector<aiNode*> nodesToProcess = { scene->mRootNode };

	for (unsigned int i = 0; i < nodesToProcess.size(); i++)
	{
		aiNode* node = nodesToProcess[i];
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			meshes.push_back(processAIMesh(scene->mMeshes[node->mMeshes[i]], scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			nodesToProcess.push_back(node->mChildren[i]);
		}
	}

	//std::cout << "LOADED MODEL: " << path << std::endl;
}

Model::~Model()
{
}

void Model::Draw(ShaderProgram& shader)
{
	for (Mesh mesh : meshes)
	{
		mesh.Draw(shader);
	}
}

Mesh Model::processAIMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture2D> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int i = 0; i < face.mNumIndices; i++)
		{
			indices.push_back(face.mIndices[i]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
	}

	return Mesh(vertices, indices, textures);
}
