#pragma once

#include "System.h"

#include "Transform.h"
#include "Model.h"
#include "EntityHandle.h"
#include "Window.h"


class BasicRenderSystem : public RenderSystem {
private:
	std::unique_ptr<Shader> basicShader;
	const EntityHandle* camera;
	const Window::Dimensions* windowDimensions;
public:
	BasicRenderSystem(const EntityHandle* camera, const Window::Dimensions* windowDimensions);

	void init() override;

	void render() override;
private:
	glm::mat4 getViewMat();

	glm::mat4 getProjectionMat();
};