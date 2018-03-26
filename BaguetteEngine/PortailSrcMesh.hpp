#pragma once

#include "AMesh.hpp"
#include "EasyCamera.hpp"

#include "TextureRenderer.hpp"
#include "SceneGraph.hpp"

class PortailSrcMesh : public AMesh
{
public:
	PortailSrcMesh(SceneGraph & scene);
	virtual ~PortailSrcMesh(void);

	void setDest(AMesh *dest);

private:
	virtual void draw_(void);

private:
	SceneGraph & scene_;
	AMesh * dest_;
	ofPlanePrimitive plane_;
	EasyCamera cam_;
	ofFbo fbo_;
	TextureRenderer renderer_;
	bool r_;
};