#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <bullet/btBulletDynamicsCommon.h>

#include <glm/glm.hpp>

namespace Converter {
	btVector3 aiVecTobtVec(const aiVector3D& vec) {
		return btVector3(vec.x, vec.y, vec.z);
	}

	glm::vec3 btVectoVec(const btVector3& vec) {
		return glm::vec3(vec.x(), vec.y(), vec.z());
	}
}