#pragma once

#include "Shader.h"
#include "Model.h"

#include <unordered_map>

namespace Renderer {
	void attachTextures(const std::vector<Texture>& textures, const Shader& shader);
	void renderMesh(const Mesh& mesh, const Shader& shader);
	void renderModel(const Model& model, const Shader& shader);

	std::unordered_map<aiTextureType, std::string> uniformPrefixes = {
		{ aiTextureType_DIFFUSE,  "textureDiffuse" },
		{ aiTextureType_SPECULAR, "textureSpecular"},
		{ aiTextureType_HEIGHT,   "textureNormal"  },
	};


	void attachTextures(const std::vector<Texture>& textures, const Shader& shader) {
		std::unordered_map<aiTextureType, unsigned int> textureNums;

		for (unsigned int i = 0; i < textures.size(); i++) {
			Texture texture = textures[i];

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture.id);


			unsigned int& textureNum = textureNums.emplace(texture.textureType, 0).first->second;

			// Set uniform name and increment
			std::string uniformName = "material." + uniformPrefixes[texture.textureType] + std::to_string(textureNum++);
			shader.setInt(uniformName, i);
		}

		glActiveTexture(GL_TEXTURE0);
	}

	void renderMesh(const Mesh& mesh, const Shader& shader) {
		attachTextures(mesh.textures, shader);

		glBindVertexArray(mesh.VAO);

		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void renderModel(const Model& model, const Shader& shader) {
		shader.use();

		for (const Mesh& mesh : model.meshes) {
			renderMesh(mesh, shader);
		}
	}
};