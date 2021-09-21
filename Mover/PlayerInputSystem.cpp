#include "EntityHandle.h"
#include "PlayerInputSystem.h"
#include "PlayerInput.h"
#include "Transform.h"
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
	// Clamsp a number around a lower and upper bound. If it is larger of smaller, it wraps around.
	if (num < lower) {
		return num + (upper - lower);
	} else if (num > upper) {
		return num - (upper - lower);
	}
	return num;
}

float getPitch(const glm::vec3& front) {
	// Calculates the pitch from the front vector relative to (0, 0, -1)
	return glm::degrees(asin(front.y));
}

float getYaw(const glm::vec3& front) {
	// Calculates the yaw from the front vector relative to (0, 0, -1)
	glm::vec2 initialSide = glm::vec2(1, 0);
	glm::vec2 terminalSide = glm::normalize(glm::vec2(-front.z, -front.x));
	return glm::degrees(atan2(initialSide.x * terminalSide.y - terminalSide.x * initialSide.y, glm::dot(initialSide, terminalSide)));

}
void PlayerInputSystem::update() {
	float speed = 0.2f;
	for (auto& player : entities) {
		auto& input = player.getComponent<PlayerInput>().input;
		auto& playerTansform = player.getComponent<Transform>();


		auto& camera = player.getComponent<View>().viewCamera;
		auto& cameraTransform = camera.getComponent<Transform>();
		auto& cameraComponent = camera.getComponent<CameraComponent>();

		// Interprets the keyboard input.
		Transform::Directions playerDirections = playerTansform.getDirectionVectors();

		if (input->isPressed(GLFW_KEY_W)) {
			playerTansform.position += playerDirections.front * speed;
		}
		if (input->isPressed(GLFW_KEY_S)) {
			playerTansform.position -= playerDirections.front * speed;
		}
		if (input->isPressed(GLFW_KEY_A)) {
			playerTansform.position -= playerDirections.right * speed;
		}
		if (input->isPressed(GLFW_KEY_D)) {
			playerTansform.position += playerDirections.right * speed;
		}
		if (input->isPressed(GLFW_KEY_UP)) {
			playerTansform.position += playerDirections.up * speed;
		}
		if (input->isPressed(GLFW_KEY_DOWN)) {
			playerTansform.position -= playerDirections.up * speed;
		}


		// Camera and player rotations;
		if (firstMousePoll) {
			firstMousePoll = false;
			prevMouseX = input->mouseX;
			prevMouseY = input->mouseY;
		}

		float dYaw = -(input->mouseX - prevMouseX) * 0.1f;
		float dPitch = -(input->mouseY - prevMouseY) * 0.1f;

		prevMouseX = input->mouseX;
		prevMouseY = input->mouseY;

		glm::vec3 cameraFront = cameraTransform.getFront();

		float pitch = getPitch(cameraFront), yaw = getYaw(cameraFront);

		yaw = wrap(yaw + dYaw, -180.0f, 180.0f);
		pitch = glm::clamp(pitch + dPitch, -89.0f, 89.0f);

		glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
		glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));
		playerTansform.rotation = qYaw;

		// Links the camera to the player
		cameraTransform.position = playerTansform.position;
		cameraTransform.rotation = qYaw * qPitch;
	}
}