#include "PlanGenerator.hpp"

PlanGenerator::PlanGenerator()
{
	plan_.setPosition(ofVec3f(0, 0, 0));
	plan_.setSize(1, 1);
}

PlanGenerator::PlanGenerator(const ofVec2f pos, const float width, const float height)
{
	plan_.setPosition(pos);
	plan_.setSize(width, height);
}

AMesh PlanGenerator::operator()(void) const
{
	return generate();
}

AMesh PlanGenerator::generate() const
{
	return plan_;
}

void PlanGenerator::setSize(const float width, const float height)
{
	plan_.setSize(width, height);
}

void PlanGenerator::setPosition(const ofVec3f pos)
{
	plan_.setPosition(pos);
}
