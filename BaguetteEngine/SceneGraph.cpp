#include "SceneGraph.hpp"
#include "ARenderer.hpp"

SceneGraph::SceneGraph(void)
	: root_(new SceneNode(0))
{
	// root_->setTransformMatrix(ofMatrix4x4::newIdentityMatrix());
}

SceneGraph::~SceneGraph(void)
{
	// tout delete
}

void SceneGraph::update(float dt)
{
	root_->update(dt);
}

void SceneGraph::render(ARenderer & renderer)
{
	root_->render(renderer);
}

const Identifiable & SceneGraph::attachTo(SceneNode::Ptr child, const Identifiable & parent)
{
	try {
		return root_->attachTo(std::move(child), parent);
	}
	catch (const std::runtime_error & e)
	{
		throw (e);
	}
}

SceneNode::Ptr SceneGraph::detach(const Identifiable & parent)
{
	return root_->detach(parent);
}