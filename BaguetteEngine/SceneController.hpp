#pragma once

#include <vector>
#include <sstream>

#include "ofxAssimpModelLoader.h"
#include "AMesh.hpp"
#include "SphereGenerator.hpp"
#include "PlanGenerator.hpp"
#include "CubeGenerator.hpp"
#include "ConeGenerator.hpp"

#include "SceneGraph.hpp"

class ARenderer;

// Singleton ?
class SceneController
{
public:
	enum InstantiableMesh
	{
		SPHERE,
		PLAN,
		BOX,
		CONE
	};

public:
	SceneController(void);
	~SceneController(void);

	void update(float dt);
	void render(ARenderer & renderer);

	int selected(int x, int y);

	const Identifiable & instanciateMesh(InstantiableMesh meshType, const Identifiable & parent = Identifiable());
	void removeMesh(const Identifiable & meshId);

	void setMeshPosition(const Identifiable & meshId, const ofVec3f & pos);
	void setMeshRotation(const Identifiable & meshId, float degrees, const ofVec3f & axis);
	void setMeshScale(const Identifiable & meshId, const ofVec3f & scale);
	void setMeshColor(const Identifiable & meshId, const ofFloatColor & color);

	void graphContent(SceneNode::TreeData & data) const;

private:
	SceneNode * ensureMeshExistance(const Identifiable & id);

private:
	ofEasyCam cam_;
	SceneGraph graph_;
};