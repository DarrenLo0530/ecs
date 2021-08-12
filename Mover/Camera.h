#pragma once
#include "EntityHandle.h"

#include "Transform.h"
#include "CameraComponent.h"

namespace Camera {
	EntityHandle createCamera(EntityHandle& camera) {
		Transform transform{};
		camera.addComponent(transform);

		CameraComponent cameraComponent{};
		camera.addComponent
	}
}