#include "Graphics.h"
#include "Shader.h"
#include "Utilities.h"
#include <vector>
#include <iostream>

Shader::Shader(){

}

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath){
	shader = createShader(vertexFilepath,fragmentFilepath);
}

Shader::~Shader(){
	glDeleteProgram(shader);
	std::cout << "Deleted shaders." << std::endl;
}

void Shader::useShader(){
	// Get shader created in Window init.
	glUseProgram(shader);
}

unsigned int Shader::getShader(){
	return shader;
}

void Shader::bind(){
	glUseProgram(shader);
}

bool Shader::bindUniform(const char* name, const glm::mat4& value){
	int i = glGetUniformLocation(shader, name);
	if (i < 0) {
		std::cout << "\x1B[31m!!!ERROR: Shader uniform not found mat4. \033[0m\t\t" << name << std::endl;
		return false;
	}
	glUniformMatrix4fv(i, 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::vec3& value){
	int i = glGetUniformLocation(shader, name);
	if (i < 0) {
		std::cout << "\x1B[31m!!!ERROR: Shader uniform not found vec3. \033[0m\t\t" << name << std::endl;
		return false;
	}
	
	glUniform3f(i, value.x,value.y, value.z);
	return true;
}

bool Shader::bindUniform(const char* name, const float value){
	int i = glGetUniformLocation(shader, name);
	if (i < 0) {
		std::cout << "\x1B[31m!!!ERROR: Shader uniform not found float. \033[0m\t\t"  << name << std::endl;
		return false;
	}
	glUniform1f(i,value);
	return true;
}

bool Shader::bindUniform(const char* name, const int value){
	int i = glGetUniformLocation(shader, name);
	if (i < 0) {
		std::cout << "\x1B[31m!!!ERROR: Shader uniform not found int. \033[0m\t\t" << name << std::endl;
		return false;
	}
	glUniform1i(i, value);
	return true;
}

unsigned int Shader::createShader(const std::string& vertexFilepath, const std::string& fragmentFilepath){
	std::vector<unsigned int> modules;
	std::cout << "Begin creation of Vertex shader..." << std::endl;
	modules.push_back(createModule(vertexFilepath, GL_VERTEX_SHADER));
	std::cout << "Created vertex shader." << std::endl;
	std::cout << "Begin creation of Fragment shader..." << std::endl;
	modules.push_back(createModule(fragmentFilepath, GL_FRAGMENT_SHADER));
	std::cout << "Created fragment shader." << std::endl;

	unsigned int shader = glCreateProgram();
	for (unsigned int shaderModule : modules) {
		glAttachShader(shader, shaderModule);
	}
	glLinkProgram(shader);


	// Check if the shader modules were linked correctly.
	int success;
	glGetShaderiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "\x1B[31m!!!ERROR: Shader linking error:\n.\033[0m" << errorLog << std::endl;
	}
	// Delete shader modules
	for (unsigned int shaderModule : modules) {
		glDeleteShader(shaderModule);
	}
	std::cout << "ShaderProgram created." << std::endl;
	return shader;
}

unsigned int Shader::createModule(const std::string& filepath, unsigned int moduleType){
	std::string shaderSource = LoadFileAsString(filepath);
	const char* shaderSrc = shaderSource.c_str();
	unsigned int shaderModule = glCreateShader(moduleType);
	// Note: glShaderSource() source, 1 source code, memory address of source, length of the string to use - NULL for whole string.
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	// Check if the shader module was compiled correctly.
	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "\x1B[31m!!!ERROR: Failed to compile shader module:\n.\033[0m" << errorLog << std::endl;

	}
	return shaderModule;
}
