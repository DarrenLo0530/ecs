#pragma once
#include "Component.h"
#include "EntityHandle.h"

struct View : public Component<View> {
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;

	glm::vec3 worldUp;

	View() : front{ glm::vec3(0.0, 0.0, -1.0) }, worldUp{ glm::vec3(0.0, 1.0, 0.0) } {
		updateVectors();
	}

	void updateVectors() {
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};