#pragma once

#include "ofMain.h"

#include "Identifiable.hpp"
#include "SceneNode.hpp"

class ARenderer;

static int cpt = 0;

class SceneGraph
{
public:
	template <typename T>
	static SceneNode::Ptr CreateSceneNode(void)
	{
		SceneNode::Ptr node(new SceneNode(++cpt));
		node->setDrawable(new T);
		return std::move(node);
	}

	template <typename T, typename U>
	static SceneNode::Ptr CreateSceneNode(void)
	{
		SceneNode::Ptr node(new SceneNode(++cpt));
		node->setDrawable(new T(U()()));
		return std::move(node);
	}

	template <typename T, typename U>
	static SceneNode::Ptr CreateSceneNode(const std::string &path)
	{
		SceneNode::Ptr node(new SceneNode(++cpt));
		node->setDrawable(new T(U(path)()));
		return std::move(node);
	}


public:
	SceneGraph(void);
	~SceneGraph(void);

	void update(float dt);
	void render(ARenderer & renderer);

	const Identifiable & attachTo(SceneNode::Ptr child, const Identifiable & parent);
	SceneNode::Ptr detach(const Identifiable & node);

	SceneNode * findNode(const Identifiable & id);
	void dump(SceneNode::TreeData & graph) const;

private:
	SceneNode::Ptr root_;
};