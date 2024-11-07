#pragma once
#include "Camera.h"
#include "Program.h"
#include "Shader.h"
#include <glm.hpp>
#include <ext.hpp>
#include "RenderObject.h"
#include <vector>

#include "Light.h"
using glm::mat4;


class MyGame : public Program
{
public:
	MyGame();
	~MyGame();
	bool startup() override;
	void update(float delta) override;
	void draw(Camera* cam, Shader* shader) override;
	

protected:
	std::vector<RenderObject*> renderObjects;
	glm::vec3 ambientLight;

	DirectionalLight directionalLight;
	PointLight pointLight;
	
	
};

