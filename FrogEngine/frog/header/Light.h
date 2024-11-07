#pragma once
struct Light {
	glm::vec3 color;

};
struct DirectionalLight : Light {
	glm::vec3 direction;
	void ApplyToShader(Shader* shader) {
		shader->bindUniform("directionalLight.direction", direction);
		shader->bindUniform("directionalLight.color", color);
	}
};
struct PointLight : Light {
	glm::vec3 position;
	int index;
	void ApplyToShader(Shader* shader) {
		shader->bindUniform(("pointLights[" + std::to_string(index) + "].position").c_str(), position);
		shader->bindUniform(("pointLights[" + std::to_string(index) + "].color").c_str(), color);
	}
};