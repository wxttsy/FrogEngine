#include "Camera.h"
#include "Application.h"
#include <ext.hpp>
#include <iostream>

glm::mat4 Camera::GetViewMatrix(){
	float thetaRadians = glm::radians(theta);
	float phiRadians = glm::radians(phi);
	glm::vec3 forward(cos(phiRadians) * cos(thetaRadians), sin(phiRadians), cos(phiRadians) * sin(thetaRadians));
	return glm::lookAt(position, position + forward, glm::vec3(0,1,0));
}

glm::mat4 Camera::GetProjectionMatrix(float windowWidth, float windowHeight){
	return glm::perspective(glm::pi<float>() * 0.25f, windowWidth / windowHeight, 0.1f, 1000.f);
}

void Camera::update(GLFWwindow* window,float delta){
	float thetaRadians = glm::radians(theta);
	float phiRadians = glm::radians(phi);

	// Calculate the forward, up and right axis for this camera.
	glm::vec3 forward(cos(phiRadians) * cos(thetaRadians), sin(phiRadians), cos(phiRadians) * sin(thetaRadians));
	glm::vec3 right(-sin(thetaRadians), 0, cos(thetaRadians));
	glm::vec3 up(0, 1, 0);

	// Use WASD, ZX keys to move the camera around
	if (glfwGetKey(window, GLFW_KEY_X))
		position += up * delta * 3.0f;
	if (glfwGetKey(window, GLFW_KEY_Z))
		position -= up * delta * 3.0f;
	if (glfwGetKey(window, GLFW_KEY_W))
		position += forward * delta * 3.0f;
	if (glfwGetKey(window, GLFW_KEY_S))
		position -= forward * delta * 3.0f;
	if (glfwGetKey(window, GLFW_KEY_D))
		position += right * delta * 3.0f;
	if (glfwGetKey(window, GLFW_KEY_A))
		position -= right * delta * 3.0f;

	glm::vec2 mouseDelta = Application::get()->getMouseDelta();

	const float turnSpeed = 0.1f;
	// If the right mouse button is held down, increment theta and phi
	if (glfwGetMouseButton(window, 1)) {
		theta += turnSpeed * mouseDelta.x;
		phi -= turnSpeed * mouseDelta.y;
	}
}
