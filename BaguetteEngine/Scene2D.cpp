#include "Scene2D.hpp"

Scene2D::Scene2D(void)
{
}

Scene2D::~Scene2D(void)
{
}

const Identifiable & Scene2D::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	ensureDrawableExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (type == "triangle")
		node = SceneGraph::CreateSceneNode<TriangleVector>();
	else if (type == "ellipse")
		node = SceneGraph::CreateSceneNode<EllipseVector>();
	else if (type == "point")
		node = SceneGraph::CreateSceneNode<PointVector>();
	else if (type == "circle")
		node = SceneGraph::CreateSceneNode<PointVector>();
	else if (type == "rectangle")
		node = SceneGraph::CreateSceneNode<RectangleVector>();
	else
		std::cerr << type << " not found !" << std::endl;
	try {
		const Identifiable & id = graph_.attachTo(std::move(node), parent);
		setDrawablePosition(id, ofVec3f(ofGetWidth() / 2.f, ofGetHeight() / 2.f));
		setDrawableScale(id, ofVec3f(100, 100));
		focusedMesh_ = &id;
		return id;
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

std::string Scene2D::getName(void) const
{
	return "Surface Editor";
}

int Scene2D::getNbDimensions(void) const
{
	return 2;
}