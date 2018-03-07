#pragma once

#include "IBasicMeshGenerator.hpp"

class SphereGenerator : IBasicMeshGenerator
{
public:
	ofMesh operator()(void) const;
	ofMesh generate() const;
	void setRadius(const float radius);
	void setPosition(const ofVec2f pos);


private:
	ofSpherePrimitive	sphere_;
};