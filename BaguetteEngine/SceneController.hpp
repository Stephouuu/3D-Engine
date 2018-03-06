#pragma once

#include "AMesh.hpp"
#include "SphereGenerator.hpp"

class ARenderer;

// Singleton ?
class SceneController
{
public:
	SceneController(void);
	~SceneController(void);

	void update(float dt);
	void render(ARenderer & renderer);

private:
	ofEasyCam cam_;
	AMesh mesh_;
};