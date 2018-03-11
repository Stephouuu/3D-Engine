#include "SmileVectorShape.hpp"

SmileVectorShape::SmileVectorShape(void)
{
}

SmileVectorShape::~SmileVectorShape(void)
{
}

void SmileVectorShape::update(float dt)
{
}

void SmileVectorShape::draw(ARenderer & renderer)
{

}

void SmileVectorShape::setFillColor(const ofColor & color)
{
}

const ofColor & SmileVectorShape::getFillColor(void) const
{
	return circle_.getFillColor();
}

void SmileVectorShape::setOutlineColor(const ofColor & color)
{
}

const ofColor &SmileVectorShape::getOutlineColor(void) const
{
	return circle_.getOutlineColor();
}

void SmileVectorShape::setOutlineThickness(int thickness)
{
}

int SmileVectorShape::getOutlineThickness(void) const
{
	return 0;
}

void SmileVectorShape::setTexture(Texture * texture)
{
}

void SmileVectorShape::invalidate(void)
{
	const ofVec3f & pos = getPosition();
}