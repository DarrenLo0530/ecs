#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Window.h"

struct CameraComponent : public Component<CameraComponent> {
	float pitch = 0.0f;
	float yaw = 0.0f;

	float FOV = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	const Window::Dimensions* viewport = nullptr;
};