#include "RenderObject.h"

RenderObject::RenderObject()
{
}

RenderObject::~RenderObject()
{
}

RenderObject::RenderObject(const char* objFile, const char* mtlFile, float _scale, vec3 _pos){
	mesh.initialiseFromFile(objFile);
	mesh.loadMaterial(mtlFile);

	transform = {
		  _scale,0,0,0,
		  0,_scale,0,0,
		  0,0,_scale,0,
		  _pos.x,_pos.y,_pos.z,1
	};
	position = _pos;
	scale = _scale;
}

void RenderObject::draw(mat4 pv, Shader* shader){
	auto pvm = pv * transform;
	shader->bindUniform("ProjectionViewModel", pvm);
	shader->bindUniform("ModelMatrix", transform);
	mesh.applyMaterial(shader);
	mesh.draw();
}

void RenderObject::setPosition(vec3 pos){
	transform = {
		  scale,0,0,0,
		  0,scale,0,0,
		  0,0,scale,0,
		  pos.x,pos.y,pos.z,1
	};
	position = pos;
}

void RenderObject::setScale(float _scale){
	transform = {
		  _scale,0,0,0,
		  0,_scale,0,0,
		  0,0,_scale,0,
		  position.x,position.y,position.z,1
	};
	scale = _scale;
}