#pragma once
#include "Shader.h"
#include <glm.hpp>
#include <ext.hpp>
using glm::mat4;
class Program
{
public:
	virtual bool startup() = 0;
	virtual void update(float delta) = 0;
	virtual void draw(Camera* cam, Shader* shader) = 0;

	int windowWidth = 1280;
	int windowHeight = 720;
	const char* title = "Default Window Title - Sarah is cool.";
};

