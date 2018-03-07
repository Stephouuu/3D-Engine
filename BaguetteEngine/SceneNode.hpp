#pragma once

#include <memory>
#include <vector>

#include "ofMain.h"

#include "AMesh.hpp"

class ARenderer;

class SceneNode
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode(int id);
	~SceneNode(void);

	void render(ARenderer & renderer);

	AMesh *getMesh(void);

private:
	int id_;
	// ofNode node_;
	// AMesh *mesh_;
	std::vector<Ptr> childs_;
	AMesh *mesh_;
};