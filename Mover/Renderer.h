#pragma once

#include "Shader.h"
#include "Model.h"

namespace Renderer {
	void renderModel(const Model& model, const Shader& shader) {
		shader.use();	

		for(const Mesh& mesh : model.meshes) {
			renderMesh(mesh);
		}
	}


	void renderMesh(const Mesh& mesh) {
		glDrawElements(GL_EL)
	}
};