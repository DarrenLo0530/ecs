#pragma once
#include "RigidBody.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "Converter.h"

namespace MeshColliderLoader {
	void processNode(aiNode* node, const aiScene* scene, btTriangleMesh* meshCollider);
	void processMesh(aiMesh* mesh, btTriangleMesh* meshCollider);
	btTriangleMesh* loadMeshCollider(std::string path);

	btTriangleMesh* loadMeshCollider(std::string path) {

		// Import scene
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			// Scene was not loaded in properly
			throw importer.GetErrorString();
		}


		btTriangleMesh* meshCollider = new btTriangleMesh();

		// Start processing nodes recursively
		processNode(scene->mRootNode, scene, );
		return meshCollider;
	}


	void processNode(aiNode* node, const aiScene* scene, btTriangleMesh* meshCollider) {
		// Node stores indices of meshes stored in the Scene

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			// Get index of node's meshes
			unsigned int meshIndex = node->mMeshes[i];

			// Get actual mesh from the index store in the scene
			aiMesh* mesh = scene->mMeshes[meshIndex];
		}


		// Recursivly process child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene, meshCollider);
		}
	}

	void processMesh(aiMesh* mesh, btTriangleMesh* meshCollider) {
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace& face = mesh->mFaces[i];
			meshCollider->addTriangle(
				Converter::aiVecTobtVec(mesh->mVertices[face.mIndices[0]]),
				Converter::aiVecTobtVec(mesh->mVertices[face.mIndices[1]]),
				Converter::aiVecTobtVec(mesh->mVertices[face.mIndices[2]])
			);
		}
	}
}