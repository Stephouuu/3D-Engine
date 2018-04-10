#include "SceneGraph.hpp"
#include "ARenderer.hpp"
#include "CubePrimitive.hpp"

SceneGraph::SceneGraph(void)
	: root_(new SceneNode(0))
{
	root_->setName("Scene root");
	root_->setDrawable(new CubePrimitive);
	root_->getDrawable()->setPosition(ofVec3f(0, 0, 0));
	root_->getDrawable()->setFillColor(ofColor(0, 0, 0, 0));
}

SceneGraph::~SceneGraph(void)
{
}

void SceneGraph::update(float dt)
{
	root_->update(dt);
}

void SceneGraph::render(ARenderer & renderer, const ofCamera & camera, LightShader &lightShader)
{
	// std::cout << "cam #" << camId << std::endl;
	root_->render(renderer, camera, lightShader);
}

const Identifiable & SceneGraph::attachTo(SceneNode::Ptr child, const Identifiable & parent)
{
	if (child->getID() == 0) {
		throw std::runtime_error("ID 0 is reserved to the scene root object");
	}

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

SceneNode * SceneGraph::findNode(const Identifiable & id)
{
	return root_->findNode(id);
}

void SceneGraph::dump(SceneNode::TreeData & graph) const
{
	root_->dump(graph);
}