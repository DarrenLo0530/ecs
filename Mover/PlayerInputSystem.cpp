#include "PlayerInputSystem.h"
#include "PlayerInput.h"
#include "Transform.h"
#include "EntityHandle.h"
#include "View.h"
#include "CameraComponent.h"
#include <glm/gtx/euler_angles.hpp>

void PlayerInputSystem::init() {

	// Players must have a view camera, transform and input component to be abl to be controllable
	registerComponent<View>();
	registerComponent<PlayerInput>();
	registerComponent<Transform>();
}

float wrap(float num, float lower, float upper) {
	if (num < lower) {
		return num + (upper - lower);
	} else if (num > upper) {
		return num - (upper - lower);
	}

	return num;
}

void PlayerInputSystem::update() {
	float speed = 0.2f;
	for (auto& player : entities) {
		auto& input = player.getComponent<PlayerInput>().input;
		auto& playerTansform = player.getComponent<Transform>();


		auto& camera = player.getComponent<View>().viewCamera;
		auto& cameraTransform = camera.getComponent<Transform>();
		auto& cameraComponent = camera.getComponent<CameraComponent>();


		// Keyboard input

		if (input->isPressed(GLFW_KEY_W)) {
			playerTansform.position += playerTansform.front * speed;
		}
		if (input->isPressed(GLFW_KEY_S)) {
			playerTansform.position -= playerTansform.front * speed;
		}
		if (input->isPressed(GLFW_KEY_A)) {
			playerTansform.position += playerTansform.right * speed;
		}
		if (input->isPressed(GLFW_KEY_D)) {
			playerTansform.position -= playerTansform.right * speed;
		}
		if (input->isPressed(GLFW_KEY_UP)) {
			playerTansform.position += playerTansform.up * speed;
		}
		if (input->isPressed(GLFW_KEY_DOWN)) {
			playerTansform.position -= playerTansform.up * speed;
		}

		// Camera and player rortations;

		if (firstMousePoll) {
			firstMousePoll = false;
			prevMouseX = input->mouseX;
			prevMouseY = input->mouseY;
		}

		glm::vec3 test = glm::eulerAngles(cameraTransform.rotation);

		// std::cout << input->mouseX - prevMouseX << std::endl;
		float dYaw = (input->mouseX - prevMouseX) * 0.1f;
		float dPitch = (input->mouseY - prevMouseY) * 0.1f;

		float& yaw = cameraComponent.yaw;
		float& pitch = cameraComponent.pitch;

		yaw += dYaw;
		pitch += dPitch;

		yaw = wrap(yaw, -180.0f, 180.0f);
		pitch = glm::clamp(pitch, -89.0f, 89.0f);


		glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
		glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));

		cameraTransform.rotation = glm::normalize( qPitch * qYaw );

		prevMouseX = input->mouseX;
		prevMouseY = input->mouseY;


		// Link player and camera;

		// Mouse input
		cameraTransform.updateDirections();
	}
}