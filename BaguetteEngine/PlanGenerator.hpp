#pragma once

#include "IBasicMeshGenerator.hpp"

class PlanGenerator : IBasicMeshGenerator
{
public:
	PlanGenerator();
	PlanGenerator(const ofVec2f pos, const float width, const float height);
	AMesh operator()(void) const;
	AMesh generate() const;
	void setSize(const float width, const float height);
	void setPosition(const ofVec3f pos);

private:
	ofPlanePrimitive plan_;
};