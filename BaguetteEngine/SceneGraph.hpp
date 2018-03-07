#pragma once

#include "ofMain.h"

#include "Identifiable.hpp"
#include "SceneNode.hpp"

class ARenderer;

class SceneGraph
{
public:
	template <typename T>
	static SceneNode::Ptr CreateSceneNode(void)
	{
		static int cpt = 1;
		SceneNode::Ptr node(new SceneNode(cpt));
		node->setMesh(new AMesh(T()()));
		++cpt;
		return std::move(node);
	}

public:
	SceneGraph(void);
	~SceneGraph(void);

	void update(float dt);
	void render(ARenderer & renderer);

	const Identifiable & attachTo(SceneNode::Ptr child, const Identifiable & parent);
	SceneNode::Ptr detach(const Identifiable & node);

private:
	SceneNode::Ptr root_;
};