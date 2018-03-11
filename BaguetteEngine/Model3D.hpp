#pragma once

#include <vector>

#include "ofxAssimpModelLoader.h"
#include "AMesh.hpp"

class Model3D : public AMesh
{
public:
	Model3D();
	virtual ~Model3D();
	bool load(const string &path);

private:
	virtual void draw_(void);

	ofxAssimpModelLoader		model_;
	ofMesh						modelMesh_;
};