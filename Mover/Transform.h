#pragma once

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform : public Component<Transform> {
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	Transform() : 
		position { glm::vec3(0.0) }, 
		rotation {glm::vec3(0.0)}, 
		scale {glm::vec3(1.0)} {}
};