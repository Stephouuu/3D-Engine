#include "SceneNode.hpp"

SceneNode::SceneNode(int id)
	: Identifiable(id), parent_(nullptr), mesh_(nullptr)
{
}

SceneNode::~SceneNode(void)
{
}

void SceneNode::update(float dt)
{
	if (mesh_) {
		mesh_->update(dt);
	}
}

void SceneNode::render(ARenderer & renderer)
{
	if (mesh_) {
		mesh_->draw(renderer);
	}
	for (auto & it : childs_) {
		it->render(renderer);
	}
}

const Identifiable & SceneNode::attachTo(SceneNode::Ptr child, const Identifiable & parent)
{
	SceneNode *nodeParent = findNode(parent);
	if (nodeParent) {
		child->setParent(nodeParent);
		childs_.push_back(std::move(child));
		return *childs_.back();
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

void SceneNode::setMesh(AMesh *mesh)
{
	mesh_ = mesh;
}

void SceneNode::setParent(SceneNode *parent)
{
	if (mesh_ && parent->getMesh()) {
		parent_ = parent;
		mesh_->setParent(*parent->getMesh());
	}
}

AMesh *SceneNode::getMesh(void)
{
	return (mesh_);
}

SceneNode *SceneNode::findNode(const Identifiable & node)
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