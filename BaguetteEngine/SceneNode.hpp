#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include "ofMain.h"

#include "AMesh.hpp"
#include "Identifiable.hpp"
#include "SceneNode.hpp"

class ARenderer;

class SceneNode : public Identifiable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode(int id);
	~SceneNode(void);

	void update(float dt);
	void render(ARenderer & renderer);

	const Identifiable & attachTo(SceneNode::Ptr child, const Identifiable & parent);
	SceneNode::Ptr detach(const Identifiable & node);
	void destroy(void);

	void setMesh(AMesh *mesh);
	void setParent(SceneNode *parent);

	AMesh *getMesh(void);

	SceneNode * findNode(const Identifiable & node);
	void dump(int depth = 0);

private:
	const Identifiable & addChild(SceneNode::Ptr child);

private:
	std::vector<Ptr> childs_;
	AMesh *mesh_;
};