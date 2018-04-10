#pragma once

#include "ofFbo.h"
#include "Identifiable.hpp"
#include "EasyCamera.hpp"
#include "SceneGraph.hpp"
#include "ARenderer.hpp"

class Portail
{
public:
	Portail(const Identifiable & p1, const Identifiable & p2);
	~Portail(void);

	bool refresh(ARenderer & renderer, SceneGraph & scene, LightShader & lightShader);

private:
	void updateCamerasTransformation(SceneNode *n1, SceneNode *n2);
	void updatePortalTextures(SceneNode *n1, SceneNode *n2);

private:
	Identifiable p1_;
	Identifiable p2_;
	EasyCamera pcam1_;
	EasyCamera pcam2_;
	ofFbo fbo1_;
	ofFbo fbo2_;
};

