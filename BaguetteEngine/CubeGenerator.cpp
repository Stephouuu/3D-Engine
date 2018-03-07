#include "CubeGenerator.hpp"

CubeGenerator::CubeGenerator()
{
	box_.setPosition(ofVec3f(0, 0, 0));
	box_.set(0.5f, 0.5f, 0.5f);
}

CubeGenerator::CubeGenerator(const float width, const float height, const float depth)
{
	box_.set(width, height, depth);
}

AMesh CubeGenerator::operator()(void) const
{
	return generate();
}

AMesh CubeGenerator::generate() const
{
	return AMesh(box_.getMesh());
}

void CubeGenerator::setSize(const float width, const float height, const float depth)
{
	box_.set(width, height, depth);
}

void CubeGenerator::setPosition(const ofVec3f pos)
{
	box_.setPosition(pos);
}
