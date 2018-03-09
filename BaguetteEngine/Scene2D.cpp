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
	else
		std::cerr << type << " not found !" << std::endl;
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

int Scene2D::getNbDimensions(void) const
{
	return 2;
}