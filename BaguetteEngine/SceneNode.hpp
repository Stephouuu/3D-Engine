#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include "ofMain.h"

// #include "AMesh.hpp"
#include "ADrawable.hpp"
#include "Identifiable.hpp"
#include "SceneNode.hpp"

class ARenderer;

class SceneNode : public Identifiable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::vector<std::pair<int, const Identifiable &> > TreeData;

public:
	SceneNode(int id);
	~SceneNode(void);

	void update(float dt);
	void render(ARenderer & renderer, const ofCamera & camera);

	const Identifiable & attachTo(SceneNode::Ptr child, const Identifiable & parent);
	SceneNode::Ptr detach(const Identifiable & node);
	void destroy(void);

	void setDrawable(ADrawable * drawable);
	void setParent(SceneNode *parent);

	ADrawable * getDrawable(void) const;

	SceneNode * findNode(const Identifiable & node);
	void dump(TreeData & graph, int depth = 0) const;

private:
	const Identifiable & addChild(SceneNode::Ptr child);

private:
	std::vector<Ptr> childs_;
	ADrawable *drawable_;
};