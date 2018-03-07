#pragma once

#include <vector>

#include "ofMain.h"

class ARenderer;

class AMesh : public ofNode
{
public:
	AMesh(void);
	// AMesh(const & std::vector<>)
	AMesh(const ofMesh & oMesh);
	virtual ~AMesh(void);

	AMesh operator=(const ofMesh &oMesh);
	void setMesh(const ofMesh &oMesh);

	virtual void draw(ARenderer & renderer);

private:
	ofVboMesh vbo_;
	ofShader shader_;
};