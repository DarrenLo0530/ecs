#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>



class Shader {
public:
	bool linked;
	unsigned int ID;

	// Constructor
	Shader(const char* vShaderPath, const char* fShaderPath);

	void attachShader(const char* path, GLenum shaderType);

	void link();

	void use() const;

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setMat4(const std::string& name, glm::mat4 value) const;

	void setVec2(const std::string& name, glm::vec2 value) const;

	void setVec3(const std::string& name, glm::vec3 value) const;

	void bindTexture(const std::string& name, GLenum textureType, unsigned int texture, unsigned int textureUnit) const;
private:
	std::vector<unsigned int> attachedShaders;
};
