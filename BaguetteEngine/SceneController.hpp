#pragma once

#include <vector>
#include "ofxAssimpModelLoader.h"
#include "AMesh.hpp"
#include "SphereGenerator.hpp"
#include "PlanGenerator.hpp"

#include "SceneGraph.hpp"

class ARenderer;

// Singleton ?
class SceneController
{
public:
	SceneController(void);
	~SceneController(void);

	void update(float dt);
	void render(ARenderer & renderer);

	int selected(int x, int y);

	enum InstatiableMesh
	{
		SPHERE,
		PLAN
	};

	int instanciateMesh(InstatiableMesh meshType, float x = 0, float y = 0, float z = 0);

private:
	ofEasyCam cam_;
	AMesh mesh1_;
	AMesh mesh2_;
	std::vector<AMesh> scenegraph_;
	SceneGraph graph_;
};