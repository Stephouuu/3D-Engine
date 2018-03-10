#pragma once

#include "ofxAssimpModelLoader.h"
#include "AMesh.hpp"

class Model3D : public AMesh
{
public:
	Model3D();
	virtual ~Model3D();
	bool load(const string &path);

private:
	ofxAssimpModelLoader		model_;
};