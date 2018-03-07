#pragma once

#include "ofMain.h"

#include "SceneNode.hpp"

class ARenderer;

class SceneGraph
{
public:
	SceneGraph(void);
	~SceneGraph(void);

	void update(float dt);
	void render(ARenderer & renderer);

	void attachTo(int idParent);
	SceneNode::Ptr detach(int id); // todo: return the detached child

private:
	SceneNode root_;
};