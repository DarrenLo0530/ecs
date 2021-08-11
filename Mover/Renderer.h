#pragma once

#include "Shader.h"

class Renderer {
public:
	void draw(unsigned int vao, Shader& shader);
};