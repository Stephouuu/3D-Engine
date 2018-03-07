#include "SceneController.hpp"
#include "ARenderer.hpp"

SceneController::SceneController(void)
{
	cam_.setDistance(10);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);

	SphereGenerator sphere;
	sphere.setRadius(1);

	PlanGenerator	plan;
	plan.setSize(1, 1);

	mesh1_ = sphere.generate();
	mesh1_.setPosition(ofVec3f(6, 1, 0));

	mesh2_ = plan.generate();
	mesh2_.setPosition(ofVec3f(4, 4, 0));
	mesh2_.setScale(ofVec3f(1, 1, 1));
}

SceneController::~SceneController(void)
{

}

void SceneController::update(float dt)
{
	// ...
}

void SceneController::render(ARenderer & renderer)
{
	cam_.begin();

	//This is just for Anthony test	
	mesh1_.draw(renderer);
	mesh2_.draw(renderer);

	cam_.end();
}

int SceneController::selected(int x, int y)
{
	//Il faut v�rifier dans le graph de sc�ne si un objet correspond � ces coordonn�es et renvoyer son id
	return -1;
}

int SceneController::instanciateMesh(float x, float y, float z)
{
	return 0;
}
