#include "Lights.h"




Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, 0.5f,  0.1f)},
	Vertex{glm::vec3(-0.1f, 0.5f, -0.1f)},
	Vertex{glm::vec3(0.1f, 0.5f, -0.1f)},
	Vertex{glm::vec3(0.1f, 0.5f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.7f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.7f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.7f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.7f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


glm::vec4 Lights::getLightColor()
{
	return lightColor;
}

glm::vec3 Lights::getLightPos()
{
	return lightPos;
}



Lights::Lights()
{
}

void Lights::init()
{
	std::string texPath = "resources/textures/";
	Texture textures[]
	{
		Texture((texPath + "planks.png").c_str(), "diffuse", 0),
		Texture((texPath + "planksSpec.png").c_str(), "specular", 1)
	};

	// Shader for ligh cube
	lightShader = Shader("resources/shaders/light.vert", "resources/shaders/light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create ligh mesh
	lightMeshes.push_back(Mesh(lightVerts, lightInd, tex));


	// Take care of all the light related things
	lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}

void Lights::display(Camera camera)
{
	for (unsigned int i = 0; i < lightMeshes.size(); i++)
	{
		lightMeshes[i].Mesh::Draw(lightShader, camera);
	}
}


void Lights::destroy()
{
	lightShader.Delete();
}