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

	const Identifiable & sphereId = instanciateMesh(InstantiableMesh::SPHERE);
	setMeshPosition(sphereId, ofVec3f(5, 0, 2));
	const Identifiable & planId = instanciateMesh(InstantiableMesh::PLAN, sphereId);
	setMeshPosition(planId, ofVec3f(0, 2, 0));
	// removeMesh(planId);
	setMeshColor(planId, ofFloatColor::orange);
	setMeshColor(sphereId, ofFloatColor::red);
}

SceneController::~SceneController(void)
{
}

void SceneController::update(float dt)
{
	graph_.update(dt);
}

void SceneController::render(ARenderer & renderer)
{
	cam_.begin();
	ofDrawGrid(1.25f, 8U, false, false, true, false);

	graph_.render(renderer);
	// ofDrawAxis(2); // x = red ; y = green ; z = blue.
	cam_.end();
}

int SceneController::selected(int x, int y)
{
	//Il faut vérifier dans le graph de scène si un objet correspond à ces coordonnées et renvoyer son id
	return -1;
}

const Identifiable & SceneController::instanciateMesh(InstantiableMesh meshType, const Identifiable & parent)
{
	SceneNode::Ptr node = nullptr;

	if (meshType == InstantiableMesh::SPHERE)
		node = SceneGraph::CreateSceneNode<SphereGenerator>();
	else if (meshType == InstantiableMesh::PLAN)
		node = SceneGraph::CreateSceneNode<PlanGenerator>();
	try {
		return graph_.attachTo(std::move(node), parent);
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

void SceneController::removeMesh(const Identifiable & meshId)
{
	graph_.detach(meshId);
}

void SceneController::setMeshPosition(const Identifiable & meshId, const ofVec3f & pos)
{
	SceneNode *node = graph_.findNode(meshId);

	if (node) {
		node->getMesh()->setPosition(pos);
	}
	else {
		std::ostringstream oss;
		oss << "Mesh #" << meshId << " not found" << std::endl;
		throw std::runtime_error(oss.str());
	}
}

void SceneController::setMeshScale(const Identifiable & meshId, const ofVec3f & scale)
{
	SceneNode *node = graph_.findNode(meshId);

	if (node) {
		node->getMesh()->setScale(scale);
	}
	else {
		std::ostringstream oss;
		oss << "Mesh #" << meshId << " not found" << std::endl;
		throw std::runtime_error(oss.str());
	}
}

void SceneController::setMeshColor(const Identifiable & meshId, const ofFloatColor & color)
{
	SceneNode *node = graph_.findNode(meshId);

	if (node) {
		node->getMesh()->setColor(color);
	}
	else {
		std::ostringstream oss;
		oss << "Mesh #" << meshId << " not found" << std::endl;
		throw std::runtime_error(oss.str());
	}
}