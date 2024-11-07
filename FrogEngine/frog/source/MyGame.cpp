#include "Graphics.h"
#include "MyGame.h"
#include <iostream>
#include "glm.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

MyGame::MyGame(){
	windowWidth = 1280;
	windowHeight = 720;
	title = "Frog Engine";	
}

MyGame::~MyGame(){
	
}

bool MyGame::startup() {
	renderObjects.push_back(new RenderObject("frog/img/lily.glb", "frog/img/lily.mtl", 0.2, glm::vec3(0, 0, 0)));
	renderObjects.push_back(new RenderObject("frog/img/bottle.glb", "frog/img/bottle.mtl", 1, glm::vec3(2, 2, 0)));
	directionalLight.direction = { -1,-1,-1 };
	directionalLight.color = { 1,0.8,0.8 }; // Color of the light
	ambientLight = { 0.55f,0.55f,0.55f }; // Intensity

	pointLight.position = { 0,0,0 };
	pointLight.color = { 1.0f,0.5f,0.5f };
	pointLight.index = 0;

	return true;
}

void MyGame::update(float delta){
	
}

void MyGame::draw(Camera* cam, Shader* shader){
	//Change clear colour
	glClearColor(0.5, 0.5f, 0.5f, 1);

	// Set up camera stuff for mesh
	glm::mat4 pv = cam->GetProjectionMatrix((float)windowWidth, (float)windowHeight) * cam->GetViewMatrix();

	pointLight.position = cam->getPosition();
	// Bind the shader
	shader->bind();
	shader->bindUniform("cameraPosition", cam->getPosition());
	shader->bindUniform("AmbientColor", ambientLight);

	// Apply Game Lights to the shader
	directionalLight.ApplyToShader(shader);
	pointLight.ApplyToShader(shader);
	// Draw RenderObjects
	for (RenderObject* object : renderObjects) {
		object->draw(pv, shader);
	}

	// Draw ImGui stuff
	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Sunlight Direction", &directionalLight.direction[0], 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat3("Sunlight Color", &directionalLight.color[0], 0.01f, 0.0f, 1.0f);
	ImGui::End();

	// Lily
	ImGui::Begin("Lily Rendered Object");
	ImGui::DragFloat3("X, Y, Z", (float*) & renderObjects[0]->position, 0.1f, -50.0f, 50.0f);
	renderObjects[0]->setPosition(renderObjects[0]->position);
	ImGui::DragFloat("Scale", (float*)&renderObjects[0]->scale, 0.1f, -50.0f, 50.0f);
	renderObjects[0]->setScale(renderObjects[0]->scale);
	ImGui::End();

	// Planet
	ImGui::Begin("Planet Rendered Object");
	ImGui::DragFloat3("X, Y, Z", (float*)&renderObjects[1]->position, 0.1f, -50.0f, 50.0f);
	renderObjects[1]->setPosition(renderObjects[1]->position);
	ImGui::DragFloat("Scale", (float*)&renderObjects[1]->scale, 0.1f, -50.0f, 50.0f);
	renderObjects[1]->setScale(renderObjects[1]->scale);
	ImGui::End();
}