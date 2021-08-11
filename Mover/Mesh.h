#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>

struct Texture {
	unsigned int id;
	aiTextureType textureType;
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Mesh {
	const static unsigned int IDX_POSITION = 0;
	const static unsigned int IDX_NORMAL = 1;
	const static unsigned int IDX_TEX_COORD = 2;

	unsigned int VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int getVAO() const;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}

private:
	void setupMesh() {
		unsigned int VBO, EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

		const int stride = sizeof(Vertex);

		glEnableVertexAttribArray(IDX_POSITION);
		glVertexAttribPointer(IDX_POSITION, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

		glEnableVertexAttribArray(IDX_NORMAL);
		glVertexAttribPointer(IDX_NORMAL, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(IDX_TEX_COORD);
		glVertexAttribPointer(IDX_TEX_COORD, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, texCoord));

		glBindVertexArray(0);
	}
};

