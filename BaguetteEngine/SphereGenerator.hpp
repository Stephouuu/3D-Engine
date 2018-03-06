#pragma once

#include "IBasicMeshGenerator.hpp"
#include "AMesh.hpp"

class SphereGenerator : IBasicMeshGenerator
{
public:
	AMesh operator()(void) const;
	AMesh generate() const;
	void setRadius(const float radius);
	void setPosition(const ofVec2f pos);


private:
	ofSpherePrimitive	sphere_;
};