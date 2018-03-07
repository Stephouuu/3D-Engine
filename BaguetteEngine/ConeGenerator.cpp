#include "ConeGenerator.hpp"

ConeGenerator::ConeGenerator()
{
	cone_.setPosition(ofVec3f(0, 0, 0));
	cone_.setSize(1.0f, 2);
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
	return cone_;
}

void ConeGenerator::setSize(const float radius, const float height)
{
	cone_.setSize(radius, height);
}

void ConeGenerator::setPosition(const ofVec3f pos)
{
	cone_.setPosition(pos);
}
