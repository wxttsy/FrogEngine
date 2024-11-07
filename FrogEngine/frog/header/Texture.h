#pragma once
#include "Graphics.h"


class Texture
{
public:
	Texture();
	Texture(const char* filemame);
	~Texture();
	void load(const char* filename);
	void bind(unsigned int slot) const;
private:
	GLuint ID;
};

