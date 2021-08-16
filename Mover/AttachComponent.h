#pragma once
#include "EntityHandle.h"
#include "Component.h"
#include <glm/glm.hpp>

struct AttachComponent : Component<AttachComponent> {
	EntityHandle attachedEntity;
	glm::vec3 offset;

	AttachComponent() : offset(glm::vec3(0.0)) {}
};