#include "SceneNode.hpp"

SceneNode::SceneNode(int id)
	: Identifiable(id), drawable_(nullptr)
{
}

SceneNode::~SceneNode(void)
{
	destroy();
}

void SceneNode::update(float dt)
{
	if (drawable_) drawable_->update(dt);
	for (auto & it : childs_) it->update(dt);
}

void SceneNode::render(ARenderer & renderer, const ofCamera & camera, LightShader & lightShader)
{
	if (drawable_ && getID() != 0)
	{
		if (drawable_->haveOtherShader() == false)
			drawable_->setShader(&lightShader);
		drawable_->draw(renderer);
	}
	for (auto & it : childs_)
	{
		it->render(renderer, camera, lightShader);
	}
}

const Identifiable & SceneNode::attachTo(SceneNode::Ptr child, const Identifiable & parent)
{
	SceneNode *nodeParent = findNode(parent);
	if (nodeParent) {
		child->setParent(nodeParent);
		return nodeParent->addChild(std::move(child));
	}
	std::ostringstream oss;
	oss << "Can't find the parent #" << parent.getID() << " in the scene graph.";
	throw std::runtime_error(oss.str());
}

SceneNode::Ptr SceneNode::detach(const Identifiable & node)
{
	std::vector<Ptr>::iterator found =
		std::find_if(childs_.begin(), childs_.end(), [&] (Ptr & p) -> bool {
			return p->getID() == node.getID();
		});

	if (found != childs_.end()) {
		Ptr result = std::move(*found);
		result->setParent(nullptr);
		childs_.erase(found);
		return result;
	}

	for (auto & it : childs_) {
		SceneNode::Ptr n = std::move(it->detach(node));
		if (n) return n;
	}
	return nullptr;
}

void SceneNode::destroy(void)
{
	for (auto & it : childs_) it->destroy();
	if (drawable_) {
		delete (drawable_);
		drawable_ = nullptr;
	}
}

void SceneNode::setDrawable(ADrawable * drawable)
{
	drawable_ = drawable;
}

void SceneNode::setParent(SceneNode *parent)
{
	if (!parent) {
		drawable_->clearParent();
	}
	else if (drawable_ && parent->getDrawable()) {
		drawable_->setParent(*parent->getDrawable());
	}
}

ADrawable * SceneNode::getDrawable(void) const
{
	return (drawable_);
}

SceneNode * SceneNode::findNode(const Identifiable & node)
{
	if (getID() == node.getID()) {
		return this;
	}
	for (auto & it : childs_) {
		SceneNode *n = it->findNode(node);
		if (n) return n;
	}
	return nullptr;
}

void SceneNode::dump(TreeData & graph, int depth) const
{
	graph.emplace_back(depth, *static_cast<const Identifiable *>(this));
	for (auto & it : childs_) {
		it->dump(graph, depth + 1);
	}
}

const Identifiable & SceneNode::addChild(SceneNode::Ptr child)
{
	childs_.push_back(std::move(child));
	return *childs_.back();
}