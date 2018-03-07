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
