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
	sphere.setPosition(ofVec3f(0, 0, 0));
	sphere.setRadius(0.1);

	ofMesh mesh = sphere.generate();
	mesh.draw();
	//END Anthony test

	mesh_.draw(renderer);
	
	cam_.end();
}