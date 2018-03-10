#include "Scene3D.hpp"

Scene3D::Scene3D(void)
{
	cam_.setDistance(10);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);

	cam_.setPosition(ofVec3f(0, 10, 5));
	cam_.rotate(0, 0, 0, 0);
	cam_.lookAt(ofVec3f(0, 0, 0));

	// demo
	/*const Identifiable & sphereId = instanciateDrawable("sphere");
	setDrawablePosition(sphereId, ofVec3f(5, 0, 2));
	const Identifiable & planId = instanciateDrawable("plane", sphereId); // drew in (5, 2, 2).
	setDrawablePosition(planId, ofVec3f(0, 2, 0));

	const Identifiable & plan2Id = instanciateDrawable("plane");
	setDrawablePosition(plan2Id, ofVec3f(0, 1, 0));
	setDrawableRotation(plan2Id, 20, ofVec3f(1, 1, 0));

	setDrawablePosition(plan2Id, ofVec3f(3, 0, 3));
	setDrawableColor(planId, ofColor::orange);
	setDrawableColor(sphereId, ofColor::red);

	// removeMesh(planId);

	SceneNode::TreeData data;
	graphContent(data);
	std::clog << " Scene graph: " << std::endl;
	for (auto & it : data) {
		for (int i = 0; i < it.first; ++i) {
			std::clog << "-";
		}
		std::clog << " " << "id: " << it.second.getID() << " name: " << it.second.getName() << std::endl;
	} */
}

Scene3D::~Scene3D(void)
{
}

void Scene3D::render(ARenderer & renderer)
{
	cam_.begin();
	ofDrawGrid(1, 8U, false, false, true, false);
	// ofDrawAxis(2); // x = red ; y = green ; z = blue.
	AScene::render(renderer);
	cam_.end();
}

const Identifiable & Scene3D::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	ensureDrawableExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (type == "sphere")
		node = SceneGraph::CreateSceneNode<AMesh, SphereGenerator>();
	else if (type == "plane")
		node = SceneGraph::CreateSceneNode<AMesh, PlaneGenerator>();
	else if (type == "cube")
		node = SceneGraph::CreateSceneNode<AMesh, CubeGenerator>();
	else if (type == "cone")
		node = SceneGraph::CreateSceneNode<AMesh, ConeGenerator>();
	else
		std::cerr << type << " not found !" << std::endl;
	try {
		const Identifiable & id = graph_.attachTo(std::move(node), parent);
		historic_.pushTransformation(std::make_pair(id, ofMatrix4x4::newIdentityMatrix()));
		return id;
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

std::string Scene3D::getName(void) const
{
	return "World Editor";
}

int Scene3D::getNbDimensions(void) const
{
	return 3;
}