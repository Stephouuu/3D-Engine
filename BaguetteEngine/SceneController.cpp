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

	// demo
	const Identifiable & sphereId = instanciateMesh(InstantiableMesh::SPHERE);
	setMeshPosition(sphereId, ofVec3f(5, 0, 2));
	const Identifiable & planId = instanciateMesh(InstantiableMesh::PLAN, sphereId); // drew in (5, 2, 2).
	setMeshPosition(planId, ofVec3f(0, 2, 0));
	const Identifiable & plan2Id = instanciateMesh(InstantiableMesh::PLAN);
	setMeshPosition(plan2Id, ofVec3f(0, 1, 0));
	setMeshRotation(plan2Id, 20, ofVec3f(1, 1, 0));
	// removeMesh(planId);
	setMeshColor(planId, ofFloatColor::orange);
	setMeshColor(sphereId, ofFloatColor::red);

	/* Dump graph scene content - to use with GUI */
	SceneNode::TreeData data;
	graphContent(data);
	std::clog << " Scene graph: " << std::endl;
	for (auto & it : data) {
		for (int i = 0; i < it.first; ++i) {
			std::clog << "-";
		}
		std::clog << " " << "id: " << it.second.getID() << " name: " << it.second.getName() << std::endl;
	}
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
	ofDrawGrid(1, 8U, false, false, true, false);

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
	ensureMeshExistance(meshId);
	graph_.detach(meshId);
}

void SceneController::setMeshPosition(const Identifiable & meshId, const ofVec3f & pos)
{
	ensureMeshExistance(meshId)->getMesh()->setPosition(pos);
}

void SceneController::setMeshRotation(const Identifiable & meshId, float degrees, const ofVec3f & axis)
{
	ensureMeshExistance(meshId)->getMesh()->rotate(degrees, axis);
}

void SceneController::setMeshScale(const Identifiable & meshId, const ofVec3f & scale)
{
	ensureMeshExistance(meshId)->getMesh()->setScale(scale);
}

void SceneController::setMeshColor(const Identifiable & meshId, const ofFloatColor & color)
{
	ensureMeshExistance(meshId)->getMesh()->setColor(color);
}

void SceneController::graphContent(SceneNode::TreeData & data) const
{
	graph_.dump(data);
}

SceneNode * SceneController::ensureMeshExistance(const Identifiable & id)
{
	SceneNode *node = graph_.findNode(id);

	if (!node) {
		std::ostringstream oss;
		oss << "Mesh #" << id << " not found" << std::endl;
		throw std::runtime_error(oss.str());
	}
	return node;
}