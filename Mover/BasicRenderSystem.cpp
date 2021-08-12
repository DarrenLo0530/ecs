#include "BasicRendererSystem.h"
#include "CameraComponent.h"

void BasicRendererSystem::init() {
		registerComponent<Model>();
		registerComponent<Transform>();

		basicShader = new Shader("basicShader.vert", "basicShader.frag");
}

void BasicRendererSystem::render() {
	for (const auto& entity : entities) {
		auto& transform = entity.getComponent<Transform>();
		auto& model = entity.getComponent<Model>();

		glm::mat4 modelMat = glm::mat4(1.0);
		glm::translate(modelMat, transform.position);
		modelMat *= glm::mat4_cast(transform.rotation);
		glm::scale(modelMat, transform.scale);

		basicShader->setMat4("model", modelMat);

		basicShader->setMat4("view", getViewMat());
		basicShader->setMat4("projection", getProjectionMat());

		Renderer::renderModel(model, *basicShader);
	}
}

void BasicRendererSystem::setCamera(EntityHandle* camera) {
	this->camera = camera;
}

glm::mat4 BasicRendererSystem::getViewMat() {
	auto& cameraTransform = camera->getComponent<Transform>();
	auto& cameraComponent = camera->getComponent<CameraComponent>();

	return glm::lookAt(cameraTransform.position, cameraTransform.position + cameraComponent.front, cameraComponent.up);
}

glm::mat4 BasicRendererSystem::getProjectionMat() {
	return glm::mat4(1.0);
}



