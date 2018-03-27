#pragma once

#include "ofMain.h"

#include "Identifiable.hpp"
#include "SceneNode.hpp"

class ARenderer;

static int cpt = 0;

class SceneGraph
{
public:
	template <typename T, typename... Args>
	static SceneNode::Ptr CreateSceneNode(Args & ... args)
	{
		SceneNode::Ptr node(new SceneNode(++cpt));
		node->setDrawable(new T(args...));
		return std::move(node);
	}

	template <typename T, typename... Args>
	static SceneNode::Ptr CreateSceneNodeFromGenerator(Args & ... args)
	{
		SceneNode::Ptr node(new SceneNode(++cpt));
		node->setDrawable(T(args...)());
		return std::move(node);
	}

public:
	SceneGraph(void);
	~SceneGraph(void);

	void update(float dt);
	void render(ARenderer & renderer, const ofCamera & camera = ofCamera());

	const Identifiable & attachTo(SceneNode::Ptr child, const Identifiable & parent);
	SceneNode::Ptr detach(const Identifiable & node);

	SceneNode * findNode(const Identifiable & id);
	void dump(SceneNode::TreeData & graph) const;

private:
	SceneNode::Ptr root_;
};