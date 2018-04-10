#pragma once

#include <vector>
#include <cmath>
#include <random>

#include "AScene.hpp"

#include "Sphere.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

class SceneRaytracer : public AScene
{
public:
	SceneRaytracer(void);
	virtual ~SceneRaytracer(void);

	virtual void update(float dt);
	virtual void render(ARenderer & renderer);

	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	virtual std::string getName(void) const;
	virtual int getNbDimensions(void) const;

	virtual CameraController & getCameraController(void);

private:
	void init(void);

private:
	CameraController cc_;
	ofImage img_;
	bool init_;
	int w_;
	int h_;
};

