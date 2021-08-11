#pragma once

#include "Mesh.h"

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stb_image.h>

namespace TextureLoader {
	std::unordered_map<std::string, unsigned int> loadedTextures = {};

	const unsigned int loadTexture2DUtil(std::string filePath, GLenum internalFormat, GLenum format, GLenum storage, bool withMipMap) {
		auto it = loadedTextures.find(filePath);
		if (it != loadedTextures.end()) {
			return it->second;
		}

		unsigned int textureId;
		glGenTextures(1, &textureId);

		// Load texture 1
		int width, height, numChannels;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);
		if (data) {
			glBindTexture(GL_TEXTURE_2D, textureId);

			// Setting parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			// Set texture data
			if (internalFormat == GL_NONE) {
				if (numChannels == 1) {
					internalFormat = GL_RED;
				} else if (numChannels == 3) {
					internalFormat = GL_RGB;
				} else if (numChannels == 4) {
					internalFormat = GL_RGBA;
				}
			}

			if (format == GL_NONE) {
				format = internalFormat;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, storage, data);

			if (withMipMap) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}


			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
		} else {
			std::cout << stbi_failure_reason() << std::endl;
			return 0;
		}

		loadedTextures.insert({ filePath, textureId });
		return textureId;
	}

	const unsigned int loadTexture2D(std::string filePath) {
		return loadTexture2DUtil(filePath, GL_NONE, GL_NONE, GL_UNSIGNED_BYTE, true);
	}

	const unsigned int loadTexture2DHDR(std::string filePath) {
		auto it = loadedTextures.find(filePath);
		if (it != loadedTextures.end()) {
			return it->second;
		}

		unsigned int textureId;
		glGenTextures(1, &textureId);

		// Load texture 1
		int width, height, numChannels;
		float* data = stbi_loadf(filePath.c_str(), &width, &height, &numChannels, 0);
		if (data) {
			glBindTexture(GL_TEXTURE_2D, textureId);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
		} else {
			std::cout << stbi_failure_reason() << std::endl;
			return 0;
		}



		loadedTextures.insert({ filePath, textureId });
		return textureId;
	}
}
