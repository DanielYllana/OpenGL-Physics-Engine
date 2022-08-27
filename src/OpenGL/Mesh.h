#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Holds number of instances (if 1 the mesh will be rendered normally)
	unsigned int instancing;

	Mesh();

	// Initializes the mesh
	Mesh
	(
		std::vector <Vertex>& vertices,
		std::vector <GLuint>& indices,
		std::vector <Texture>& textures,
		unsigned int instancing = 1,
		std::vector <glm::mat4> instanceMatrix = {}
	);




	// Draws the mesh
	void Draw
	(
		Shader& shader, 
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::mat4 manipulation = glm::mat4(1.0f)
	);
};
#endif