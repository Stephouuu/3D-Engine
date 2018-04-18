#include "BezierSpline.hpp"

BezierSpline::BezierSpline(void)
{
	p_.insert(std::begin(p_), {
		{ 150.0, 150.0, 0.0 },
		{ 250.0, 250.0, 0.0 },
		{ 450.0, 150.0, 0.0 },
		{ 550.0, 550.0, 0.0 },
		{ 550.0, 750.0, 0.0 },
		{ 750.0, 750.0, 0.0 },
		{ 800.0, 800.0, 0.0 }
	});
}

BezierSpline::~BezierSpline(void)
{
}

void BezierSpline::drawSpline(void)
{
	ofSetColor(getFillColor());
	ofNoFill();
	ofBezier(p_.at(0).x, p_.at(0).y, p_.at(1).x, p_.at(1).y, p_.at(2).x, p_.at(2).y, p_.at(3).x, p_.at(3).y);
	ofBezier(p_.at(3).x, p_.at(3).y, p_.at(4).x, p_.at(4).y, p_.at(5).x, p_.at(5).y, p_.at(6).x, p_.at(6).y);
}

void BezierSpline::invalidate(void)
{
	reallocate(ofGetWidth(), ofGetHeight());

	setOrigin({
		p_.at(0).x + (p_.at(6).x - p_.at(0).x) / 2,
		p_.at(0).y + (p_.at(6).y - p_.at(0).y) / 2
	});

	drawFboBegin();
		drawSpline();
	drawFboEnd();
}

void BezierSpline::setParam(const std::vector<ofPoint> & p)
{
	p_ = p;
	invalidate();
}

const vector<ofPoint> & BezierSpline::getParam(void) const
{
	return p_;
}