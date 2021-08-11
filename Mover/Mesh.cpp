#include "Mesh.h"
#include <map>

const unsigned int IDX_POSITION = 0;
const unsigned int IDX_NORMAL = 1;
const unsigned int IDX_TEX_COORD = 2;


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	this->vertices = vertices;
	this->indices = indices;

	setupMesh();
}

void Mesh::setupMesh() {
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
