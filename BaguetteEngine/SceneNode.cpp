#include "SceneNode.hpp"

SceneNode::SceneNode(int id)
	: id_(id)
{
}

SceneNode::~SceneNode(void)
{
}

void SceneNode::render(ARenderer & renderer)
{
	if (mesh_) {
		mesh_->draw(renderer);
	}
}

AMesh *SceneNode::getMesh(void)
{
	return (mesh_);
}