#include "DialogVectorShape.hpp"

DialogVectorShape::DialogVectorShape(void)
{
	shape_.setScale({ 400, 200, 0 });
	shape_.setFillColor(ofColor(230, 230, 230, 255));
	shape_.setOutlineColor({ 255, 0, 0, 255 });
	shape_.setOutlineThickness(3);

	bar_.setScale({ 407, 40 });
	bar_.setFillColor(ofColor(128, 128, 128, 156));

	underscore_.setScale({ 20, 2 });
	underscore_.setFillColor(ofColor::black);

	maximize_.setScale({ 18, 8 });
	maximize_.setFillColor(ofColor(0, 0, 0, 0));
	maximize_.setOutlineThickness(2);
	maximize_.setOutlineColor(ofColor::black);

	croix1_.setScale({ 2, 20 });
	croix2_.setScale({ 2, 20 });
	croix1_.setRotation(45);
	croix2_.setRotation(-45);
	croix1_.setFillColor(ofColor::black);
	croix2_.setFillColor(ofColor::black);
}

DialogVectorShape::~DialogVectorShape(void)
{
}

void DialogVectorShape::update(float dt)
{
}

void DialogVectorShape::draw(ARenderer & renderer)
{
	shape_.draw(renderer);
	bar_.draw(renderer);
	croix1_.draw(renderer);
	croix2_.draw(renderer);
	underscore_.draw(renderer);
	maximize_.draw(renderer);
}

void DialogVectorShape::setFillColor(const ofColor & color)
{
}

const ofColor & DialogVectorShape::getFillColor(void) const
{
	return shape_.getFillColor();
}

void DialogVectorShape::setOutlineColor(const ofColor & color)
{
}

const ofColor &DialogVectorShape::getOutlineColor(void) const
{
	return shape_.getOutlineColor();
}

void DialogVectorShape::setOutlineThickness(int thickness)
{
}

int DialogVectorShape::getOutlineThickness(void) const
{
	return 0;
}

void DialogVectorShape::invalidate(void)
{
	const ofVec3f & pos = getPosition();

	shape_.setPosition(pos);
	bar_.setPosition({ pos.x , pos.y - 80 });
	underscore_.setPosition({ pos.x + 125, pos.y - 77 });
	maximize_.setPosition({ pos.x + 156, pos.y - 82 });
	croix1_.setPosition({ pos.x + 185, pos.y - 82 });
	croix2_.setPosition({ pos.x + 185, pos.y - 82 });
}