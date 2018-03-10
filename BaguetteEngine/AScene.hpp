#pragma once

#include "ARenderer.hpp"
#include "Identifiable.hpp"
#include "SceneNode.hpp"

#include "SceneGraph.hpp"
#include "TransformableHistory.hpp"

class AScene
{
public:
	AScene(void);
	virtual ~AScene(void);

	void update(float dt);
	virtual void render(ARenderer & renderer);

	void removeDrawable(const Identifiable & drawableId);

	void setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save = true);
	void setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation, bool save = true);
	void setDrawableRotation(const Identifiable & drawableId, float degrees, bool save = true);
	void setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale, bool save = true);
	void setDrawableColor(const Identifiable & drawableId, const ofFloatColor & color);
	void setDrawableOutlineColor(const Identifiable & drawableId, const ofColor & color);
	void setDrawableOutlineThickness(const Identifiable & drawableId, int thickness);

	void setSceneColor(const ofColor & color);
	const ofColor & getSceneColor(void) const;

	void graphContent(SceneNode::TreeData & data) const;

	void undo(void);
	void redo(void);

	void setFocusedDrawable(const Identifiable & drawableId);
	const Identifiable * getFocusedDrawable(void) const;

	SceneNode * ensureDrawableExistance(const Identifiable & drawableId);
	
	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable()) = 0;
	virtual std::string getName(void) const = 0;
	virtual int getNbDimensions(void) const = 0;

protected:
	SceneGraph graph_;
	TransformableHistory historic_;
	float dtUpdate_;
	const Identifiable * focusedDrawable_;
	ofColor sceneColor_;
};

