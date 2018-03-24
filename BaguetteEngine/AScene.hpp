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

	virtual void update(float dt);
	virtual void render(ARenderer & renderer);

	void removeDrawable(const Identifiable & drawableId);

	virtual void setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save = true);
	virtual void setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation, bool save = true);
	virtual void setDrawableRotation(const Identifiable & drawableId, float degrees, bool save = true);
	virtual void setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale, bool save = true);
	virtual void setDrawableColor(const Identifiable & drawableId, const ofFloatColor & color);
	virtual void setDrawableOutlineColor(const Identifiable & drawableId, const ofColor & color);
	virtual void setDrawableOutlineThickness(const Identifiable & drawableId, int thickness);

	void setSceneColor(const ofColor & color);
	const ofColor & getSceneColor(void) const;

	void graphContent(SceneNode::TreeData & data) const;

	void undo(void);
	void redo(void);

	virtual void setFocusedDrawable(const Identifiable & drawableId);
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

