#pragma once

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

struct Transform : public Component<Transform> {
	glm::vec3 position = glm::vec3(0.0);
	glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
	glm::vec3 scale = glm::vec3(1.0);

	glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

	glm::vec3 worldUp = glm::vec3(0.0, 1.0, 0.0);

	void updateDirections() {
		front = glm::mat4_cast(rotation) * glm::vec4(0.0, 0.0, -1.0, 0.0);
		right = glm::cross(worldUp, front);
		up = glm::cross(front, right);
	}
};