#pragma once

#include "ofMain.h"

class ARenderer;

class AMesh
{
public:
	AMesh(void);
	virtual ~AMesh(void);

	virtual void draw(ARenderer & renderer);
private:
	ofVboMesh vbo_;
};