#include "SceneNode.hpp"

SceneNode::SceneNode(int id)
	: Identifiable(id), mesh_(nullptr)
{
}

SceneNode::~SceneNode(void)
{
	destroy();
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
	for (auto & it : childs_) {
		it->destroy();
	}
	if (mesh_) {
		delete (mesh_);
		mesh_ = nullptr;
	}
}

void SceneNode::setMesh(AMesh *mesh)
{
	mesh_ = mesh;
}

void SceneNode::setParent(SceneNode *parent)
{
	if (!parent) {
		mesh_->clearParent();
	}
	else if (mesh_ && parent->getMesh()) {
		mesh_->setParent(*parent->getMesh());
	}
}

AMesh *SceneNode::getMesh(void)
{
	return (mesh_);
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

void SceneNode::undo(void)
{
	/* if (mesh_) {
		std::clog << "undo " << getID() << std::endl;
		mesh_->undo();
	}
	for (auto & it : childs_) {
		it->undo();
	} */
}

void SceneNode::redo(void)
{
	/* if (mesh_) {
		std::clog << "redo " << getID() << std::endl;
		mesh_->redo();
	}
	for (auto & it : childs_) {
		it->redo();
	} */
}

const Identifiable & SceneNode::addChild(SceneNode::Ptr child)
{
	childs_.push_back(std::move(child));
	return *childs_.back();
}