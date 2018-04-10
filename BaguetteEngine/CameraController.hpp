#pragma once

#include <vector>
#include <iterator>

#include "EasyCamera.hpp"
#include "ARenderer.hpp"

#include "SceneGraph.hpp"
#include "Portails.hpp"

#include "LightShader.hpp"

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

	void render(ARenderer & renderer, SceneGraph & scene, LightShader & lightShader);
	void update(float dt);
	
	void setTarget(const ofVec3f & position);

	void zoom(int factor);

	void stop(void);
	void right(void);
	void left(void);

	void swapPerspectiveOrtho(bool value);
	void createPortail(const SceneNode::Ptr & n1, const SceneNode::Ptr & n2);
	const EasyCamera & getCurrentCamera(void) const;

private:
	void updateCamerasLayout(void);

private:
	std::vector<std::pair<ofFbo, EasyCamera *> > cams_;
	std::vector<std::pair<ofFbo, EasyCamera *> >::const_iterator focused_;
	Portails portails_;
};

