#pragma once

#include <vector>
#include "ofMain.h"
#include "Identifiable.hpp"

class ARenderer;

class AMesh : public ofNode
{
public:
	AMesh(void);
	AMesh(const ofMesh & oMesh);
	virtual ~AMesh(void);

	AMesh operator=(const ofMesh &oMesh);

	void init(void);
	void setMesh(const ofMesh &oMesh);

	void update(float dt);
	virtual void draw(ARenderer & renderer);

private:
	ofVboMesh	vbo_;
	ofShader	shader_;
};