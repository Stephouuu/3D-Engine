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

	void setMesh(AMesh *mesh);
	void setParent(SceneNode *parent);

	AMesh *getMesh(void);

// private:
	SceneNode * findNode(const Identifiable & node);
	// SceneNode *findNode(const Identifiable & node);

private:
	std::vector<Ptr> childs_;
	SceneNode *parent_;
	AMesh *mesh_;
};