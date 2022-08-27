#include "Ballistic-Demo.h"
#include<glm/gtx/string_cast.hpp>
#include "../../extra/helper.h"



// Vertices coordinates
Vertex verticesBallisticDemo[] =
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
	Vertex{glm::vec3(-0.1f+2.0f, 0.5f + 2.0f,  0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.1f + 2.0f, 0.5f + 2.0f, -0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.1f + 2.0f, 0.5f + 2.0f, -0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f + 2.0f, 0.5f + 2.0f,  0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.1f + 2.0f,  0.7f + 2.0f,  0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.1f + 2.0f,  0.7f + 2.0f, -0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.1f + 2.0f,  0.7f + 2.0f, -0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f + 2.0f,  0.7f + 2.0f,  0.1f + 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}
};

// Indices for vertices order
GLuint indicesBallisticDemo[] =
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







BallisticDemo::BallisticDemo() : currentShotType(BallisticDemo::ShotType::LASER)
{
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		shot->type = BallisticDemo::ShotType::UNUSED;
	}
}




void BallisticDemo::destroy()
{
	shaderProgram.Delete();
}


void BallisticDemo::fire()
{
	AmmoRound* shot;

	// Find the first available round
	for (shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type == BallisticDemo::ShotType::UNUSED) break;
	}

	// If a round wasnt found
	if (shot >= ammo + ammoRounds) return;

	switch (currentShotType)
	{
	case BallisticDemo::ShotType::PISTOL:
		shot->particle.setMass(2.0f); // 2.0kg
		shot->particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
		shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);
		shot->particle.setDamping(0.99f);
		break;

	case BallisticDemo::ShotType::ARTILLERY:
		shot->particle.setMass(200.0f); // 200.0kg
		shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
		shot->particle.setAcceleration(0.0f, -20.0f, 0.0f);
		shot->particle.setDamping(0.99f);
		break;

	case BallisticDemo::ShotType::FIREBALL:
		shot->particle.setMass(1.0f); // 1.0kg - mostly blast damage
		shot->particle.setVelocity(0.0f, 0.0f, 10.0f); // 5m/s
		shot->particle.setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
		shot->particle.setDamping(0.9f);
		break;

	case BallisticDemo::ShotType::LASER:
		// Note that this is the kind of laser bolt seen in films,
		// not a realistic laser beam!
		shot->particle.setMass(0.1f); // 0.1kg - almost no weight
		shot->particle.setVelocity(0.0f, 0.0f, 100.0f); // 100m/s
		shot->particle.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity
		shot->particle.setDamping(0.99f);
		break;
	}


	// Set the data common to all particle types
	shot->particle.setPosition(0.0f, 1.5f, 0.0f);
	shot->type = currentShotType;

	// Clear the force accumulators
	shot->particle.clearAccumulator();
}



void BallisticDemo::update()
{
	
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != BallisticDemo::ShotType::UNUSED)
		{
			shot->particle.integrate(1);

			if (shot->particle.getPosition().y < 0.0f ||
				shot->particle.getPosition().z > 200.f)
			{
				shot->type = BallisticDemo::ShotType::UNUSED;
			}
		}
	}
}





void BallisticDemo::display(Camera camera)
{
	//meshes.Draw(shaderProgram, camera);
	//model.Draw(asteroidShaderProgram, camera);
	meshes.Draw(asteroidShaderProgram, camera);
}




void BallisticDemo::init(Lights lightSource)
{
	std::string texPath = "resources/textures/";
	Texture textures[]
	{
		Texture((texPath + "planks.png").c_str(), "diffuse", 0),
		Texture((texPath + "planksSpec.png").c_str(), "specular", 1)
	};

	// Generates Shader object using shaders default.vert and default.frag
	asteroidShaderProgram = Shader("resources/shaders/instancing.vert", "resources/shaders/default.frag");
	shaderProgram = Shader("resources/shaders/default.vert", "resources/shaders/default.frag");

	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	initMeshes(tex);


	// Take care of all the light related things
	glm::vec4 lightColor = lightSource.getLightColor();
	glm::vec3 lightPos = lightSource.getLightPos();

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	asteroidShaderProgram.Activate();
	glUniform4f(glGetUniformLocation(asteroidShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(asteroidShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
}



void BallisticDemo::initMeshes(std::vector <Texture> tex)
{
	// Radius of circle around which asteroids orbit
	float radius = 100.0f;
	// How much ateroids deviate from the radius
	float radiusDeviation = 25.0f;

	// Holds all transformations for the asteroids
	std::vector <glm::mat4> instanceMatrix;

	for (unsigned int i = 0; i < ammoRounds; i++)
	{
		// Generates x and y for the function x^2 + y^2 = radius^2 which is a circle
		float x = Helper::randf(2.0f, false);
		float y = Helper::randf(2.0f, false);
		float z = Helper::randf(2.0f, false);

		// Holds transformations before multiplying them
		glm::vec3 tempTranslation;
		//glm::quat tempRotation;
		//glm::vec3 tempScale;

		// Generates a translation near a circle of radius "radius"
		tempTranslation = glm::vec3(y, z, x);


		// Generates random rotations
		//tempRotation = glm::quat(1.0f, randf(), randf(), randf());
		// Generates random scales
		//tempScale = 0.1f * glm::vec3(randf(), randf(), randf());

		// Initialize matrices
		glm::mat4 trans = glm::mat4(1.0f);
		//glm::mat4 rot = glm::mat4(1.0f);
		//glm::mat4 sca = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		trans = glm::translate(trans, tempTranslation);
		//rot = glm::mat4_cast(tempRotation);
		//sca = glm::scale(sca, tempScale);

		// Push matrix transformation
		instanceMatrix.push_back(trans);// *rot* sca);
	}

	

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(verticesBallisticDemo, verticesBallisticDemo + sizeof(verticesBallisticDemo) / sizeof(Vertex));
	std::vector <GLuint> ind(indicesBallisticDemo, indicesBallisticDemo + sizeof(indicesBallisticDemo) / sizeof(GLuint));

	meshes = Mesh(verts, ind, tex, ammoRounds, instanceMatrix);

	//std::string asteroidPath = "resources/models/asteroid/scene.gltf";
	//model = Model((asteroidPath).c_str(), ammoRounds, instanceMatrix);
}