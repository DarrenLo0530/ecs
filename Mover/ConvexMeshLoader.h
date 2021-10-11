#pragma once
#include "RigidBody.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include <glm/glm.hpp>
#include <bullet/LinearMath/btAlignedObjectArray.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>

#include <stb_image.h>

#include "Converter.h"

namespace ConvexMeshLoader {

	inline void processMesh(aiMesh* mesh, btConvexHullShape* meshCollider) {
		// Add vertices to convex hull shape
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			meshCollider->addPoint(Converter::aiVecTobtVec(mesh->mVertices[i]));
		}
	}

	inline void processNode(aiNode* node, const aiScene* scene, btConvexHullShape* meshCollider) {

		// Node stores indices of meshes stored in the Scene

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			// Get index of node's meshes
			unsigned int meshIndex = node->mMeshes[i];

			// Get actual mesh from the index store in the scene
			aiMesh* mesh = scene->mMeshes[meshIndex];
			processMesh(mesh, meshCollider);
		}


		// Recursivly process child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene, meshCollider);
		}
	}


	inline btCollisionShape* loadMeshCollider(std::string path) {

		// Import scene
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			// Scene was not loaded in properly
			throw importer.GetErrorString();
		}

		btConvexHullShape* preMeshCollider = new btConvexHullShape();

		// Start processing nodes recursively
		processNode(scene->mRootNode, scene, preMeshCollider);
		preMeshCollider->setMargin(0);

		btShapeHull* hull = new btShapeHull(preMeshCollider);
		hull->buildHull(0);
		btConvexHullShape* postMeshCollider = new btConvexHullShape((const btScalar*)hull->getVertexPointer(), hull->numVertices());


		return postMeshCollider;
	}
}