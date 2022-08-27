#include "../../cyclone/cyclone.h"
#include "../../OpenGL/Mesh.h"
#include "../../OpenGL/Lights.h"
#include "../../OpenGL/Model.h"



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

	const static unsigned ammoRounds = 5;





	AmmoRound ammo[ammoRounds];

	ShotType currentShotType;

	Mesh meshes;
	Model model;

	void fire();

	Shader shaderProgram;
	Shader asteroidShaderProgram;

	void initMeshes(std::vector <Texture> tex);

public:

	BallisticDemo();
	

	void update();

	void mouse(int button, int state, int x, int y);

	void key(unsigned char key);

	void init(Lights lightSource);

	void display(Camera camera);

	void destroy();

};