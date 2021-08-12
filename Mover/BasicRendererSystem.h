#pragma once

#include "System.h"

#include "Transform.h"
#include "Model.h"
#include "Renderer.h"
#include "EntityHandle.h"


class BasicRendererSystem : public RenderSystem {
private:
	Shader* basicShader;
	EntityHandle* camera;
public:
	void init() override;

	void render() override;
	
	void setCamera(EntityHandle* camera);

private:
	glm::mat4 getViewMat();

	glm::mat4 getProjectionMat();

};