#pragma once
#include "Model.h"
#include "TextureLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <iostream>
#include <stb_image.h>

namespace ModelLoader {
	inline Model loadModel(std::string path);
	inline void processNode(aiNode* node, const aiScene* scene);
	inline Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	inline std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType textureType);

	std::string directory;
	std::vector<Mesh> meshes;

	Model loadModel(std::string path) {
		meshes.clear();

		// Import scene
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			// Scene was not loaded in properly
			throw importer.GetErrorString();
		}

		// Get prefix of file path
		directory = path.substr(0, path.find_last_of('/'));

		// Start processing nodes recursively
		processNode(scene->mRootNode, scene);

		Model model = {};
		model.meshes = meshes;

		return model;
	}

	void processNode(aiNode* node, const aiScene* scene) {
		// Node stores indices of meshes stored in the Scene

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			// Get index of node's meshes
			unsigned int meshIndex = node->mMeshes[i];

			// Get actual mesh from the index store in the scene
			aiMesh* mesh = scene->mMeshes[meshIndex];
			meshes.push_back(processMesh(mesh, scene));
		}


		// Recursivly process child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex{};

			// Vertex position
			aiVector3D& aiPosition = mesh->mVertices[i];
			vertex.position = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);

			// Vertex normal
			aiVector3D& aiNormal = mesh->mNormals[i];
			vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);


			// Vertex texture coords
			if (mesh->mTextureCoords[0]) {
				vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			} else {
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);

		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			// Diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			// Specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

			// Normal maps
			std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType textureType) {
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
			aiString path;
			material->GetTexture(textureType, i, &path);

			std::string pathString = std::string(path.C_Str());
			Texture texture{};

			texture.id = TextureLoader::loadTexture2D(directory + "/" + pathString);
			texture.textureType = textureType;

			textures.push_back(texture);
		}

		return textures;
	}


}