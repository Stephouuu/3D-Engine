#pragma once

#include "AScene.hpp"

class SceneRaytracer : public AScene
{
public:
	SceneRaytracer(void);
	virtual ~SceneRaytracer(void);

	virtual void render(ARenderer & renderer);

	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	virtual std::string getName(void) const;
	virtual int getNbDimensions(void) const;

	virtual CameraController & getCameraController(void);

private:
	CameraController cc_;
	ofFbo fbo_;
};

