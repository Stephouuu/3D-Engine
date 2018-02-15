#pragma once

#include "AMesh.hpp"

class ARenderer;

// Singleton ?
class SceneController
{
public:
	SceneController(void);
	~SceneController(void);

	void render(ARenderer & renderer);

private:
	ofEasyCam cam_;
	AMesh mesh_;
};