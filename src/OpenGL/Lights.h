#ifndef LIGHTS_CLASS_H
#define LIGHTS_CLASS_H

#include "Mesh.h"

class Lights 
{
	
private:

	std::vector <Mesh> lightMeshes;

	Shader lightShader;

	glm::vec3 lightPos;
	glm::vec4 lightColor;

public:

	Lights();
	void init();

	void display(Camera camera);

	glm::vec4 getLightColor();

	glm::vec3 getLightPos();

	void destroy();
};

#endif