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

	//mesh1_.draw(renderer);
	//mesh2_.draw(renderer);

	std::vector<AMesh>::iterator it;
	for (it = scenegraph_.begin(); it != scenegraph_.end(); ++it)
		it->draw(renderer);

	cam_.end();
}

int SceneController::selected(int x, int y)
{
	//Il faut vérifier dans le graph de scène si un objet correspond à ces coordonnées et renvoyer son id
	return -1;
}

int SceneController::instanciateMesh(InstatiableMesh meshType, float x, float y, float z)
{
	AMesh mesh;

	if (meshType == InstatiableMesh::SPHERE)
		scenegraph_.push_back(std::move(SphereGenerator(ofVec3f(x, y, z), 0.5)()));
	else if (meshType == InstatiableMesh::PLAN)
		scenegraph_.push_back(std::move(PlanGenerator(ofVec3f(x, y, z), 0.5, 0.5)()));
	return 0;
}
