#include "PlanGenerator.hpp"

AMesh PlanGenerator::operator()(void) const
{
	return generate();
}

AMesh PlanGenerator::generate() const
{
	return AMesh(plan_.getMesh());
}

void PlanGenerator::setSize(const float width, const float height)
{
	plan_.set(width, height);
}

void PlanGenerator::setPosition(const ofVec2f pos)
{
	plan_.setPosition(pos);
}
