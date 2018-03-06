#include "SphereGenerator.hpp"

AMesh SphereGenerator::operator()(void) const
{
	return generate();
}

AMesh SphereGenerator::generate() const
{
	return AMesh(sphere_.getMesh());
}

void SphereGenerator::setRadius(const float radius)
{
	sphere_.setRadius(radius);
}

void SphereGenerator::setPosition(const ofVec2f pos)
{
	sphere_.setPosition(pos);
}
