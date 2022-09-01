#include "../../cyclone/cyclone.h"
#include "../../OpenGL/Mesh.h"
#include "../../OpenGL/Lights.h"
#include "../../OpenGL/Model.h"
#include<GLFW/glfw3.h>



class BallisticDemo
{
private:
	enum class ShotType {
		UNUSED = 0,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};


	struct AmmoRound {

		cyclone::Particle particle;
		ShotType type;
		unsigned startTime;
	};

	const static unsigned int ammoRounds = 15;




	bool canFire = true;
	AmmoRound ammo[ammoRounds];

	ShotType currentShotType;

	std::vector<Mesh> meshes;
	std::vector<Model> models;

	void fire();

	Shader shaderProgram;
	Shader asteroidShaderProgram;

	void initMeshes(std::vector <Texture> tex);
	void initMeshesInstancing(std::vector <Texture> tex);
	void initModel(std::string path);

public:

	BallisticDemo();
	

	void update();

	void Inputs(GLFWwindow* window);

	void init(Lights lightSource);

	void display(Camera camera);

	void destroy();

};