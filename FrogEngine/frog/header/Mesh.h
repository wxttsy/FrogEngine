#pragma once
#include <glm.hpp>
#include <vector>
#include "Shader.h"
#include "Texture.h"
class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
		glm::vec4 tangent;
	};
	
	void initialiseQuad();
	void initialise(unsigned int vertexCount, const Vertex* vertices,
		unsigned int indexCount = 0, unsigned int* indices = nullptr);
	void initialiseFromFile(const char* filename);

	void applyMaterial(Shader* shader);
	void loadMaterial(const char* fileName);

	virtual void draw();

	void calculateTangents(Vertex* vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices);

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;

	glm::vec3 Ka; // Ambient Color of the surface
	glm::vec3 Kd; // Diffuse color of the surface
	glm::vec3 Ks; // Specular color of the surface
	float specularPower; // Tightness of specular highlights

	Texture mapKd; // Diffuse texture map
	Texture mapKs; // Specular texture map
	Texture mapBump; // Normal map
};

