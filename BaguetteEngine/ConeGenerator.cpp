#include "ConeGenerator.hpp"



ConeGenerator::ConeGenerator()
{
	cone_.setPosition(ofVec3f(0, 0, 0));
	cone_.set(1.0f, 2);
}

ConeGenerator::~ConeGenerator()
{
}

AMesh ConeGenerator::operator()(void) const
{
	return generate();
}

AMesh ConeGenerator::generate() const
{
	return AMesh(cone_.getMesh());
}

void ConeGenerator::setSize(const float radius, const float height)
{
	cone_.set(radius, height);
}

void ConeGenerator::setPosition(const ofVec3f pos)
{
	cone_.setPosition(pos);
}
