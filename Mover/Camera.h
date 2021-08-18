#pragma once
#include "EntityHandle.h"

#include "Transform.h"
#include "CameraComponent.h"
#include "View.h"

namespace Camera {
	void createCamera(EntityHandle* camera) {
		Transform transform{};
		camera->addComponent(transform);

		CameraComponent cameraComponent{};
		camera->addComponent(cameraComponent);
	}
}