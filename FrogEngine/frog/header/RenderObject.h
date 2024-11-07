#pragma once
#include "Mesh.h"
#include "Texture.h"
using glm::mat4;
using glm::vec3;

class RenderObject
{
public:
	float scale;
	vec3 position;
	RenderObject();
	~RenderObject();
	RenderObject(const char* objFile, const char* mtlFile, float scale, vec3 pos);
	void draw(mat4 pv, Shader* shader);
	Mesh mesh;
	glm::mat4 transform;
	void setPosition(vec3 pos);
	void setScale(float _scale);
};

