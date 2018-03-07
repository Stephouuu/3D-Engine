#include "SphereGenerator.hpp"

SphereGenerator::SphereGenerator(const ofVec3f & pos, float radius)
{
	sphere_.setPosition(pos);
	sphere_.setRadius(radius);
}

SphereGenerator::SphereGenerator()
{
	sphere_.setPosition(ofVec3f(0, 0, 0));
	sphere_.setRadius(1.0f);
}

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

void SphereGenerator::setPosition(const ofVec3f pos)
{
	sphere_.setPosition(pos);
}
