#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vShaderPath, const char* fShaderPath) {
	// Creating shader program

	ID = glCreateProgram();

	attachShader(vShaderPath, GL_VERTEX_SHADER);
	attachShader(fShaderPath, GL_FRAGMENT_SHADER);
}

void Shader::attachShader(const char* shaderPath, GLenum shaderType) {
	std::string shaderSourceStr;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(shaderPath);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderSourceStr = shaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cout << "Error while reading shader file" << std::endl;
		return;
	}
	const char* shaderSource = shaderSourceStr.c_str();

	// Create shader
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	// Check for compilation errors
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "Error while compiling shader" << shaderPath << infoLog << std::endl;
	}

	glAttachShader(ID, shader);
	attachedShaders.push_back(shader);
}

void Shader::link() {
	if (linked) {
		throw "Shader program already linked";
	}

	linked = true;
	glLinkProgram(ID);

	int success;
	char infoLog[1024];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		std::cout << "Error while linking shader program" << infoLog << std::endl;
	}

	for (unsigned int shader : attachedShaders) {
		glDeleteShader(shader);
	}
	attachedShaders.clear();
}

void Shader::use() const {
	if (!linked) {
		throw "Link the program before using";
	}
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec2(const std::string& name, glm::vec2 value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::bindTexture(const std::string& name, GLenum textureType, unsigned int texture, unsigned int textureUnit) const {
	setInt(name, textureUnit);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(textureType, texture);
}
