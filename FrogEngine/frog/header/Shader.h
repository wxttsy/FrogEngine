#pragma once                                         
#include <string>
#include <glm.hpp>
using glm::mat4;

class Shader
{
public:
	const int MAX_LIGHTS = 4;
	Shader();
	Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~Shader();
	void useShader();
	unsigned int  getShader();
	void bind();
	bool bindUniform(const char* name, const glm::mat4& value);
	bool bindUniform(const char* name, const glm::vec3& value);
	bool bindUniform(const char* name, const float value);
	bool bindUniform(const char* name, const int value);
private:
	unsigned int shader = NULL;
	unsigned int createShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	unsigned int createModule(const std::string& filepath, unsigned int moduleType);
};

