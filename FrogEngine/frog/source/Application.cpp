#include "Application.h"
#include <iostream>

#include "Gizmos.h"
#include <glm.hpp>
#include <ext.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;
Application* Application::instance = nullptr;
Application::Application(){


}

Application::Application(Program* program) : game(program){
	// Set this program to be the game we want to run.
	if (program == nullptr) {
		std::cout << "\x1B[31m!!!ERROR: No Program was found attached to Application.\033[0m\t\t" << std::endl;
		return;
	}
	//Initialise GLFW, make sure it works.
	if (!glfwInit()) {
		std::cout << "\x1B[31m!!!ERROR: GLFW couldn't start.\033[0m\t\t" << std::endl;
		return;
	}
	// Set window resolution and window title here from program.
	window = glfwCreateWindow(game->windowWidth, game->windowHeight, game->title, nullptr, nullptr);
	std::cout << "Created glfwWindow successfully." << std::endl;

	// Check if window has actually been created.
	if (!window) {
		std::cout << "\x1B[31m!!!ERROR: Window does not exist - GLFW terminated.\033[0m\t\t" << std::endl;
		glfwTerminate();
		return;
	}

	// Tell GLFW that the window we created is the one we should render to.
	glfwMakeContextCurrent(window);

	// Tell GLAD to load all its OpenGL functions so we can use them.
	if (!gladLoadGL()) {
		std::cout << "\x1B[31m!!!ERROR: GLAD OpenGL functions not loaded.\033[0m\t\t" << std::endl;
		return;
	}
	std::cout << "Loaded Glad OpenGL functions." << std::endl;

	// Set background colour
	glClearColor(1, 0.5f, 1, 1);

	// Create shader:
	shader = new Shader("frog/shaders/vertex.txt", "frog/shaders/fragment.txt");
	shader->useShader();

	cam = new Camera();
}

Application::~Application(){
	delete game;
	delete shader;
	std::cout << "Closed application window" << std::endl;
	glfwTerminate();
	std::cout << "Terminated glfw." << std::endl;
}

void Application::run(){
	double fixedDelta = 1.0 / fixedFramerate;
	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	glfwSetCursorPosCallback(window, &Application::SetMousePosition);
	// Init Game application and imgui in startup();
	startup();
	// Create Gizmo's grid.
	Gizmos::create(10000, 10000, 0, 0);
	instance = this;
	while (windowExists()) {
		// Set up imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		// Get delta time for Update.
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		
		while (accumulator >= fixedDelta)
		{
			cam->update(window, float(fixedDelta));
			update((float)fixedDelta);
			accumulator -= fixedDelta;
		}

		draw();

		// Render Imgui stuff
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}

		// Tell GLFW to check if anything is going on with input, etc.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shutdown();
}
void Application::SetMousePosition(GLFWwindow* window, double x, double y){
	instance->mousePos.x = (float)x;
	instance->mousePos.y = (float)y;
}
bool Application::windowExists(){
	return !glfwWindowShouldClose(window);
}

void Application::startup(){
	// Init Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	// Init Game application.
	game->startup();
}

void Application::update(float delta){
	lastMousePos = mousePos;
	game->update(delta);	
}

void Application::draw(){
	glClearColor(0.8f, 0.8f, 1.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
	Gizmos::clear();

	// Draw Gizmos3D Grid
	Gizmos::addTransform(glm::mat4(1));
	vec4 white(0.5);
	vec4 black(0.5, 0.5, 0.5, 0.5);

	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
	
	glm::mat4 pv = cam->GetProjectionMatrix(game->windowWidth, game->windowHeight) * cam->GetViewMatrix();
	Gizmos::draw(pv);
	game->draw(cam, shader);
}

void Application::shutdown() {
	Gizmos::destroy();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}