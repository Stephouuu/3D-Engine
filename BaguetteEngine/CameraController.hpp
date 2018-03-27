#pragma once

#include <vector>

#include "EasyCamera.hpp"
#include "ARenderer.hpp"

#include "SceneGraph.hpp"
#include "Portails.hpp"

class CameraController
{
public:
	CameraController(void);
	~CameraController(void);

	void reset(void);

	void windowsResized(const ofPoint & newDimension);
	void onClick(const ofPoint & position);

	void addCamera(void);
	void removeCamera(void);

	void render(ARenderer & renderer, SceneGraph & scene);
	void update(float dt);
	
	void setTarget(const ofVec3f & position);

	void zoom(int factor);

	void stop(void);
	void right(void);
	void left(void);

	void swapPerspectiveOrtho(bool value);

	void createPortail(const Identifiable & p1, const Identifiable & p2);

private:
	void updateCamerasLayout(void);

private:
	std::vector<std::pair<ofFbo, EasyCamera *> > cams_;
	std::vector<std::pair<ofFbo, EasyCamera *> >::const_iterator focused_;
	Portails portails_;
};

