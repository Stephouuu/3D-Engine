#pragma once

#include "IBasicMeshGenerator.hpp"
#include "AMesh.hpp"

class PlanGenerator : IBasicMeshGenerator
{
public:
	AMesh operator()(void) const;
	AMesh generate() const;
	void setSize(const float width, const float height);
	void setPosition(const ofVec2f pos);


private:
	ofPlanePrimitive	plan_;
};