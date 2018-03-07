#pragma once

#include "ofMain.h"

class ARenderer;

class AMesh : public ofNode
{
public:
	AMesh(void);
	virtual ~AMesh(void);
	AMesh(const ofMesh & oMesh);
	AMesh operator=(const ofMesh &oMesh);
	void setMesh(const ofMesh &oMesh);

	virtual void draw(ARenderer & renderer);

private:
	ofVboMesh vbo_;
	ofShader shader_;
};