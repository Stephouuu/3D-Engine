#include "Scene3D.hpp"

Scene3D::Scene3D(void)
{
}

Scene3D::~Scene3D(void)
{
}

void Scene3D::update(float dt)
{
	AScene::update(dt);
	cc_.update(dt);
}

void Scene3D::render(ARenderer & renderer)
{
	/* cc_.begin();
	ofDrawGrid(1, 8U, false, false, true, false);
	// ofDrawAxis(2); // x = red ; y = green ; z = blue.
	AScene::render(renderer);
	cc_.end(); */
	cc_.render(renderer, graph_);
}

void Scene3D::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save)
{
	AScene::setDrawablePosition(drawableId, pos, save);

	SceneNode *node = ensureDrawableExistance(drawableId);
	if (node) {
		cc_.setTarget(node->getDrawable()->getPosition());
	}
}

const Identifiable & Scene3D::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	ensureDrawableExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (type == "sphere" || type == "portails")
		node = SceneGraph::CreateSceneNodeFromGenerator<SphereGenerator>();
	//else if (type == "portails") {
	//	std::cout << "lol" << std::endl;
	//	node = SceneGraph::CreateSceneNode<PortailSrcMesh>(graph_);
	//	SceneNode::Ptr nodeDst = SceneGraph::CreateSceneNode<PortailDstMesh>();

	//	PortailSrcMesh *src = dynamic_cast<PortailSrcMesh *>(node->getDrawable());
	//	PortailDstMesh *dst = dynamic_cast<PortailDstMesh *>(nodeDst->getDrawable());

	//	src->setDest(dst);
	//	dst->setSource(src);

	//	const Identifiable & id = graph_.attachTo(std::move(node), parent);
	//	graph_.attachTo(std::move(nodeDst), parent);
	//	return id;
	//}
	else if (type == "plane")
		node = SceneGraph::CreateSceneNodeFromGenerator<PlaneGenerator>();
	else if (type == "cube")
		node = SceneGraph::CreateSceneNodeFromGenerator<CubeGenerator>();
	else if (type == "cone")
		node = SceneGraph::CreateSceneNodeFromGenerator<ConeGenerator>();
	else if (type.find("/") != std::string::npos
				|| type.find("\\") != std::string::npos
				|| type.find(".") != std::string::npos)
		node = SceneGraph::CreateSceneNodeFromGenerator<Model3DGenerator>(type);
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
	return "Editeur 3D";
}

int Scene3D::getNbDimensions(void) const
{
	return 3;
}

void Scene3D::setFocusedDrawable(const Identifiable & drawableId)
{
	AScene::setFocusedDrawable(drawableId);

	SceneNode *node = ensureDrawableExistance(drawableId);
	if (node) {
		cc_.setTarget(node->getDrawable()->getPosition());
	}
}

CameraController & Scene3D::getCameraController(void)
{
	return cc_;
}