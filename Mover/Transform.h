#pragma once

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

struct Transform : public Component<Transform> {
	struct Directions {
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
	};

	glm::vec3 position = glm::vec3(0.0);
	glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
	glm::vec3 scale = glm::vec3(1.0);


	glm::vec3 getFront() {
		return rotation * glm::vec4(0, 0, -1, 0);
	}

	Directions getDirectionVectors() {
		Directions directions{};
		directions.front = getFront();
		directions.right = rotation * glm::vec4(1, 0, 0, 0);
		directions.up = rotation * glm::vec4(0, 1, 0, 0);

		return directions;
	}

};