#pragma once

#include "IBasicMeshGenerator.hpp"

class PlanGenerator : IBasicMeshGenerator
{
public:
	ofMesh operator()(void) const;
	ofMesh generate() const;
	void setSize(const float width, const float height);
	void setPosition(const ofVec2f pos);

private:
	ofPlanePrimitive plan_;
};