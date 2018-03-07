#include "PlaneGenerator.hpp"

PlaneGenerator::PlaneGenerator()
{
	plan_.setPosition(ofVec3f(0, 0, 0));
	plan_.setSize(1, 1);
}

PlaneGenerator::PlaneGenerator(const ofVec2f pos, const float width, const float height)
{
	plan_.setPosition(pos);
	plan_.setSize(width, height);
}

AMesh PlaneGenerator::operator()(void) const
{
	return generate();
}

AMesh PlaneGenerator::generate() const
{
	return plan_;
}

void PlaneGenerator::setSize(const float width, const float height)
{
	plan_.setSize(width, height);
}

void PlaneGenerator::setPosition(const ofVec3f pos)
{
	plan_.setPosition(pos);
}
