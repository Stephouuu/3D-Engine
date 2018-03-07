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
	enum InstatiableMesh
	{
		SPHERE,
		PLAN
	};

public:
	SceneController(void);
	~SceneController(void);

	void update(float dt);
	void render(ARenderer & renderer);

	int selected(int x, int y);

	/**
	** \Brief: Add a mesh in the graph scene.
	** \param meshType: The type of the mesh to be created.
	** \param parent: The ID of the parent ; 0 (root) by default.
	** \Return success: The ID of the new mesh added.
	** \Return failure: Throw runtime exception.
	**/
	const Identifiable & instanciateMesh(InstatiableMesh meshType, const Identifiable & parent = Identifiable());

private:
	ofEasyCam cam_;
	SceneGraph graph_;
};