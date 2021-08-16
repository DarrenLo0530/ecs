#include "CameraAttachSystem.h"
#include "AttachComponent.h"
#include "Transform.h"
#include "View.h"
#include "CameraComponent.h"

void CameraAttachSystem::init() {
	registerComponent<AttachComponent>();
	registerComponent<Transform>();
	registerComponent<View>();
	registerComponent<CameraComponent>();
}

void CameraAttachSystem::update() {
	for (const EntityHandle& camera : entities) {
		auto& transform = camera.getComponent<Transform>();
		auto& view = camera.getComponent<View>();
		auto& attachComponent = camera.getComponent<AttachComponent>();

		EntityHandle attachedEntity = attachComponent.attachedEntity;

		Transform attachedTransform = attachedEntity.getComponent<Transform>();
		View attachedView = attachedEntity.getComponent<View>();

		transform = attachedTransform;
		view = attachedView;
	}
}