#pragma once
#include "Graphics.h"
#include "Camera.h"
#include "Program.h"
#include "Shader.h"
#include <glm.hpp>
#include <ext.hpp>
using glm::mat4;


class Application
{
public:
	Application();
	Application(Program* program);
	~Application();
	void run();

	static Application* get() { return instance; }

	glm::vec2 getMousePosition() { return mousePos; }
	glm::vec2 getMouseDelta() { return mousePos - lastMousePos; }
	static void SetMousePosition(GLFWwindow* window, double x, double y);
private:
	bool windowExists();
	void startup();
	void update(float delta);
	void draw();
	void shutdown();
protected:
	static Application* instance;

	glm::vec2 mousePos;
	glm::vec2 lastMousePos;

	const int fixedFramerate = 60;
	GLFWwindow* window = nullptr;
	Shader* shader = nullptr;
	Program* game = nullptr;
	Camera* cam = nullptr;

	
};

