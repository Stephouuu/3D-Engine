#include "SceneController.hpp"
#include "ARenderer.hpp"

SceneController::SceneController(void)
	: focusedMesh_(nullptr)
{
	cam_.setDistance(10);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);

	cam_.setPosition(ofVec3f(0, 10, 5));
	cam_.rotate(0, 0, 0, 0);
	cam_.lookAt(ofVec3f(0, 0, 0));

	// demo
	const Identifiable & sphereId = instanciateMesh(AMesh::InstantiableMesh::SPHERE);
	setMeshPosition(sphereId, ofVec3f(5, 0, 2));
	const Identifiable & planId = instanciateMesh(AMesh::InstantiableMesh::PLANE, sphereId); // drew in (5, 2, 2).
	setMeshPosition(planId, ofVec3f(0, 2, 0));

	const Identifiable & plan2Id = instanciateMesh(AMesh::InstantiableMesh::PLANE);
	setMeshPosition(plan2Id, ofVec3f(0, 1, 0));
	setMeshRotation(plan2Id, 20, ofVec3f(1, 1, 0));

	setMeshPosition(plan2Id, ofVec3f(3, 0, 3));
	setMeshColor(planId, ofFloatColor::orange);
	setMeshColor(sphereId, ofFloatColor::red);

	// removeMesh(planId);

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

	// vector tests
	/* point_.setFillColor(ofColor::blue);
	point_.setRadius(10.f);
	point_.setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	point_.setOutlineThickness(5);
	point_.setOutlineColor(ofColor::red);
	point_.invalidate(); */

	triangle_.setFillColor(ofColor::blue);
	// triangle_.setVerticesPosition({0, 0}, {100, 0}, {100, 80});
	triangle_.setSize(100.f);
	triangle_.setRotation(45);
	triangle_.setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	// triangle_.setAlignment(AVectorPrimitive::Alignment::Middle);
	triangle_.setOutlineThickness(5);
	triangle_.setOutlineColor(ofColor::red);
	triangle_.invalidate();

	/* rectangle_.setFillColor(ofColor::blue);
	rectangle_.setDimension(200, 100);
	rectangle_.setRotation(90);
	rectangle_.setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	rectangle_.setOutlineThickness(2);
	rectangle_.setOutlineColor(ofColor::orange);
	rectangle_.invalidate(); */

	/* ellipse_.setFillColor(ofColor::blue);
	ellipse_.setDimension(200, 100);
	ellipse_.setRotation(90);
	ellipse_.setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	ellipse_.setOutlineThickness(5);
	ellipse_.setOutlineColor(ofColor::orange);
	ellipse_.invalidate(); */
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

	// point_.draw();
	triangle_.draw();
	// rectangle_.draw();
	// ellipse_.draw();
}

int SceneController::selected(int x, int y)
{
	//Il faut vérifier dans le graph de scène si un objet correspond à ces coordonnées et renvoyer son id
	return -1;
}

const Identifiable & SceneController::instanciateMesh(AMesh::InstantiableMesh meshType, const Identifiable & parent)
{
	ensureMeshExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (meshType == AMesh::InstantiableMesh::SPHERE)
		node = SceneGraph::CreateSceneNode<SphereGenerator>();
	else if (meshType == AMesh::InstantiableMesh::PLANE)
		node = SceneGraph::CreateSceneNode<PlaneGenerator>();
	else if (meshType == AMesh::InstantiableMesh::CUBE)
		node = SceneGraph::CreateSceneNode<CubeGenerator>();
	else if (meshType == AMesh::InstantiableMesh::CONE)
		node = SceneGraph::CreateSceneNode<ConeGenerator>();
	try {
		const Identifiable & id = graph_.attachTo(std::move(node), parent);
		focusedMesh_ = &id;
		historic_.pushTransformation(std::make_pair(id, ofMatrix4x4::newIdentityMatrix()));
		return id;
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

void SceneController::removeMesh(const Identifiable & meshId)
{
	ensureMeshExistance(meshId);
	historic_.deleteTransformations(meshId);
	graph_.detach(meshId);
}

void SceneController::setMeshPosition(const Identifiable & meshId, const ofVec3f & pos)
{
	SceneNode *node = ensureMeshExistance(meshId);
	
	node->getMesh()->setPosition(pos);
	historic_.pushTransformation(std::make_pair(meshId, node->getMesh()->getLocalTransformMatrix()));
}

void SceneController::setMeshRotation(const Identifiable & meshId, float degrees, const ofVec3f & axis)
{
	SceneNode *node = ensureMeshExistance(meshId);
	
	node->getMesh()->rotate(degrees, axis);
	historic_.pushTransformation(std::make_pair(meshId, node->getMesh()->getLocalTransformMatrix()));
}

void SceneController::setMeshScale(const Identifiable & meshId, const ofVec3f & scale)
{
	SceneNode *node = ensureMeshExistance(meshId);
	
	node->getMesh()->setScale(scale);
	historic_.pushTransformation(std::make_pair(meshId, node->getMesh()->getLocalTransformMatrix()));
}

void SceneController::setMeshColor(const Identifiable & meshId, const ofFloatColor & color)
{
	ensureMeshExistance(meshId)->getMesh()->setColor(color);
}

void SceneController::graphContent(SceneNode::TreeData & data) const
{
	graph_.dump(data);
}

void SceneController::undo(void)
{
	try {
		const TransformableHistory::Item & t = historic_.undo();
		SceneNode * node = graph_.findNode(t.first);
		if (node) {
			node->getMesh()->setTransformMatrix(t.second);
		}
	}
	catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
	}
}

void SceneController::redo(void)
{
	try {
		const TransformableHistory::Item & t = historic_.redo();
		SceneNode * node = graph_.findNode(t.first);
		if (node) {
			node->getMesh()->setTransformMatrix(t.second);
		}
	}
	catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
	}
}

void SceneController::setFocusedMesh(const Identifiable & id)
{
	SceneNode *node = ensureMeshExistance(id);

	if (node) {
		focusedMesh_ = node;
	}
}

const Identifiable * SceneController::getFocusedMesh(void) const
{
	// return focusedMesh_;
	return nullptr;
}

void SceneController::AddImage(const Image & img)
{
	if (img.isLoaded == true)
		cacheManager.insert(img.path, img.theImg);
	else
		throw std::invalid_argument("Cant insert an empty image.");
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