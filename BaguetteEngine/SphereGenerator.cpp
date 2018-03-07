#include "SphereGenerator.hpp"

ofMesh SphereGenerator::operator()(void) const
{
	return generate();
}

ofMesh SphereGenerator::generate() const
{
	return sphere_.getMesh();
}

void SphereGenerator::setRadius(const float radius)
{
	sphere_.setRadius(radius);
}

void SphereGenerator::setPosition(const ofVec2f pos)
{
	sphere_.setPosition(pos);
}
