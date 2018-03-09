#pragma once

#include <vector>
#include <sstream>

// #include "ofxAssimpModelLoader.h"
// #include "AMesh.hpp"

/* #include "SphereGenerator.hpp"
#include "PlaneGenerator.hpp"
#include "CubeGenerator.hpp"
#include "ConeGenerator.hpp" */

#include "Image.h" 
#include "CacheManager.hpp"

// #include "SceneGraph.hpp"
// #include "TransformableHistory.hpp"

/* #include "PointVector.hpp"
#include "TriangleVector.hpp"
#include "RectangleVector.hpp"
#include "EllipseVector.hpp" */

#include "Identifiable.hpp"
#include "SceneNode.hpp"

#include "AScene.hpp"
#include "Scene3D.hpp"

class ARenderer;

// Singleton ?
class SceneController
{
public:
	SceneController(void);
	~SceneController(void);

	void update(float dt);
	void render(ARenderer & renderer);

	const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	void removeDrawable(const Identifiable & drawableId);

	void setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos);
	void setDrawableRotation(const Identifiable & drawableId, float degrees, const ofVec3f & axis);
	void setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale);
	void setDrawableColor(const Identifiable & drawableId, const ofColor & color);

	void graphContent(SceneNode::TreeData & data) const;

	void undo(void);
	void redo(void);

	void setFocusedDrawable(const Identifiable & drawableId);
	const Identifiable * getFocusedDrawable(void) const;

	void AddImage(const Image & img);

	SceneNode * ensureDrawableExistance(const Identifiable & drawableId);

private:
	// TriangleVector triangle_;
	AScene *scene_;
	string pathkey;
	CacheManager<string, ofImage> cacheManager;
};