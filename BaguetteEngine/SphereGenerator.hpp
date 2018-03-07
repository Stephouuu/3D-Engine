#pragma once

#include "IBasicMeshGenerator.hpp"

class SphereGenerator : IBasicMeshGenerator
{
public:
	SphereGenerator(const ofVec3f & pos, float radius);
	SphereGenerator();
	AMesh operator()(void) const;
	AMesh generate() const;
	void setRadius(const float radius);
	void setPosition(const ofVec3f pos);


private:
	ofSpherePrimitive	sphere_;
};