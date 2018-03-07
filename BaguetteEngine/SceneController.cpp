#include "SceneController.hpp"
#include "ARenderer.hpp"

SceneController::SceneController(void)
{
	cam_.setDistance(5);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);
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
	SphereGenerator sphere;
	sphere.setPosition(ofVec3f(100, 0, 0));
	sphere.setRadius(0.1);

	AMesh mesh = sphere.generate();
	mesh.draw(renderer);

	PlanGenerator	plan;
	plan.setPosition(ofVec3f(0, 0, 0));
	plan.setSize(0.5, 0.5);

	plan.generate().draw(renderer);
	//END Anthony test

	mesh_.draw(renderer);

	cam_.end();
}

int SceneController::selected(int x, int y)
{
	//Il faut vérifier dans le graph de scène si un objet correspond à ces coordonnées et renvoyer son id
	return -1;
}

int SceneController::instanciateMesh(float x, float y, float z)
{
	return 0;
}
