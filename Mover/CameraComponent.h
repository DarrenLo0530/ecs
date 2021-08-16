#pragma once
#include "Component.h"
#include "glm/glm.hpp"


struct CameraComponent : public Component<CameraComponent> {
	float FOV;
	CameraComponent() : FOV(90.0f) {}
};