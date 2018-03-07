#pragma once

#include "IBasicMeshGenerator.hpp"

class SphereGenerator : IBasicMeshGenerator
{
public:
	SphereGenerator(const ofVec3f & pos, float radius);
	SphereGenerator();
	ofMesh operator()(void) const;
	ofMesh generate() const;
	void setRadius(const float radius);
	void setPosition(const ofVec2f pos);


private:
	ofSpherePrimitive	sphere_;
};