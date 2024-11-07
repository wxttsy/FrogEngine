#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {
	ID = 0;
}

Texture::Texture(const char* filename) {
	ID = 0;
	load(filename);
}

Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

void Texture::load(const char* filename) {
	int width = 0, height = 0, comp = 0;
	unsigned char* data = stbi_load(filename, &width, &height, &comp, STBI_default);
	unsigned int format;
	glGenTextures(1, &ID);

	if (data != nullptr) {
		switch (comp) {
		case STBI_grey:
			format = GL_RED;
			break;
		case STBI_grey_alpha:
			format = GL_RG;
			break;
		case STBI_rgb:
			format = GL_RGB;
			break;
		case STBI_rgb_alpha:
			format = GL_RGBA;
			break;
		default:	break;
		}
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	else {
		std::cout << "\x1B[31m!!!ERROR: Texture not loaded. \033[0m\t\t" << std::endl;
	}
	//Clean up texture
	stbi_image_free(data);
}

void Texture::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}