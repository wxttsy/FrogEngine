#pragma once
#include "Graphics.h"
#include <glm.hpp>

class Camera
{
public:
	glm::mat4 GetViewMatrix();
	glm::vec3 getPosition() { return position; };
	glm::mat4 GetProjectionMatrix(float windowWidth, float windowHeight);
	void update(GLFWwindow* window,float delta);
private:
	float theta = -45;
	float phi = -23;
	glm::vec3 position = glm::vec3(-5.7,4.1,7.2);
};

