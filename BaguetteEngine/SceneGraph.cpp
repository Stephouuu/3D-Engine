#include "SceneGraph.hpp"
#include "ARenderer.hpp"

SceneGraph::SceneGraph(void)
	: root_(0)
{
	// root_.setTransformMatrix(ofMatrix4x4::newIdentityMatrix());
}

SceneGraph::~SceneGraph(void)
{
}

void SceneGraph::update(float dt)
{

}

void SceneGraph::render(ARenderer & renderer)
{

}

void SceneGraph::attachTo(int idParent)
{

}

SceneNode::Ptr SceneGraph::detach(int id)
{
	return nullptr;
}