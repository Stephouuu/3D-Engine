#include "SmileVectorShape.hpp"

SmileVectorShape::SmileVectorShape(void)
{
	circle_.setScale({ 100, 100 });
	circle_.setFillColor(ofColor(204, 204, 0, 255));

	eye1_.setOutlineThickness(5);
	eye1_.setOutlineColor(ofColor(153, 153, 0, 255));
	eye1_.setScale(ofVec3f(30, 50));

	eye2_.setOutlineThickness(5);
	eye2_.setOutlineColor(ofColor(153, 153, 0, 255));
	eye2_.setScale(ofVec3f(30, 50));

	eye3_.setScale(ofVec3f(10, 25));
	eye3_.setFillColor(ofColor::black);

	eye4_.setScale(ofVec3f(10, 25));
	eye4_.setFillColor(ofColor::black);
}

SmileVectorShape::~SmileVectorShape(void)
{
}

void SmileVectorShape::update(float dt)
{
}

void SmileVectorShape::draw(ARenderer & renderer)
{
	circle_.draw(renderer);
	eye1_.draw(renderer);
	eye2_.draw(renderer);
	eye3_.draw(renderer);
	eye4_.draw(renderer);
}

void SmileVectorShape::setFillColor(const ofColor & color)
{
	circle_.setFillColor(color);
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

	circle_.setPosition({ pos.x, pos.y });
	eye1_.setPosition(ofVec3f(pos.x - 40, pos.y));
	eye2_.setPosition(ofVec3f(pos.x + 40, pos.y));
	eye3_.setPosition(ofVec3f(pos.x - 30, pos.y));
	eye4_.setPosition(ofVec3f(pos.x + 30, pos.y));
}