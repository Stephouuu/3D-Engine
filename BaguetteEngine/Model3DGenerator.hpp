#pragma once

#include "IBasicMeshGenerator.hpp"
#include "Model3D.hpp"

class Model3DGenerator : IBasicMeshGenerator
{
public:
	Model3DGenerator();
	Model3DGenerator(const std::string &path);
	virtual ~Model3DGenerator();
	AMesh * operator()(void) const;
	AMesh * generate() const;
	void setPosition(const ofVec3f pos);
	bool loadModel(const string &path);

private:
	Model3D			* model_;
};

