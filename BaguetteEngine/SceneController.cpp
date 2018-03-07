#include "SceneController.hpp"
#include "ARenderer.hpp"

SceneController::SceneController(void)
{
	cam_.setDistance(10);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);

	cam_.setPosition(ofVec3f(0, 10, 5));
	cam_.rotate(0, 0, 0, 0);
	cam_.lookAt(ofVec3f(0, 0, 0));
}

SceneController::~SceneController(void)
{
}

void SceneController::update(float dt)
{
	// ...
	graph_.update(dt);
}

void SceneController::render(ARenderer & renderer)
{
	cam_.begin();
	graph_.render(renderer);
	ofDrawGrid(1.25f, 8U, false, false, true, false);
	// x = red ; y = green ; z = blue.
	// ofDrawAxis(2);
	cam_.end();
}

int SceneController::selected(int x, int y)
{
	//Il faut vérifier dans le graph de scène si un objet correspond à ces coordonnées et renvoyer son id
	return -1;
}

const Identifiable & SceneController::instanciateMesh(InstatiableMesh meshType, const Identifiable & parent)
{
	SceneNode::Ptr node = nullptr;

	if (meshType == InstatiableMesh::SPHERE)
		node = SceneGraph::CreateSceneNode<SphereGenerator>();
	else if (meshType == InstatiableMesh::PLAN)
		node = SceneGraph::CreateSceneNode<PlanGenerator>();

	try {
		return graph_.attachTo(std::move(node), parent);
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}
