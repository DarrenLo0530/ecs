#include "PlayerInputSystem.h"
#include "PlayerInput.h"
#include "Transform.h"
#include "EntityHandle.h"
#include "View.h"
#include "CameraComponent.h"


void PlayerInputSystem::init() {

	// Players must have a view camera, transform and input component to be abl to be controllable

	registerComponent<View>();
	registerComponent<PlayerInput>();
	registerComponent<Transform>();

}

void PlayerInputSystem::update() {
	float speed = 0.2f;
	for (auto& entity : entities) {
		auto& input = entity.getComponent<PlayerInput>().input;
		auto& transform = entity.getComponent<Transform>();
		auto& view = entity.getComponent<View>();
		

		if (input->isPressed(GLFW_KEY_W)) {
			transform.position += view.front * speed;
		}
		if (input->isPressed(GLFW_KEY_S)) {
			transform.position -= view.front * speed;
		}
		if (input->isPressed(GLFW_KEY_A)) {
			transform.position -= view.right * speed;
		}
		if (input->isPressed(GLFW_KEY_D)) {
			transform.position += view.right * speed;
		}
		if (input->isPressed(GLFW_KEY_UP)) {
			transform.position += view.up * speed;
		}
		if (input->isPressed(GLFW_KEY_DOWN)) {
			transform.position -= view.up * speed;
		}
	}
}