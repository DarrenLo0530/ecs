#pragma once
#include "Component.h"
#include "glm/glm.hpp"


struct CameraComponent : public Component<CameraComponent> {
	float FOV;

	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;

	glm::vec3 worldUp;

	CameraComponent() : FOV(90.0f), front{ glm::vec3(0.0, 0.0, -1.0) }, worldUp { glm::vec3(0.0, 1.0, 0.0) } {
		updateVectors();
	}

	void updateVectors() {
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

};