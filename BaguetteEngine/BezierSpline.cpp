#include "BezierSpline.hpp"



BezierSpline::BezierSpline()
{
	p1 = ofPoint(150.0, 150.0, 0.0);
	p1 = ofPoint(250.0, 250.0, 0.0);
	p1 = ofPoint(450.0, 150.0, 0.0);
	p1 = ofPoint(550.0, 550.0, 0.0);
	p1 = ofPoint(550.0, 750.0, 0.0);
	p1 = ofPoint(750.0, 750.0, 0.0);
	p1 = ofPoint(800.0, 800.0, 0.0);
}


BezierSpline::~BezierSpline()
{
}

void BezierSpline::drawSpline()
{
	pointVector.push_back(p1);
	pointVector.push_back(p2);
	pointVector.push_back(p3);
	pointVector.push_back(p4);
	pointVector.push_back(p5);
	pointVector.push_back(p6);
	pointVector.push_back(p7);

	ofSetColor(100, 0, 100);
	ofDrawSphere(p1, 4);
	ofDrawSphere(p2, 4);
	ofDrawSphere(p3, 4);
	ofDrawSphere(p4, 4);
	ofDrawSphere(p5, 4);
	ofDrawSphere(p6, 4);
	ofDrawSphere(p7, 4);
	//	ofDrawSphere(p8, 4);
	ofPolyline poly(pointVector);
	//	poly.bezierTo
	poly.draw();
	ofSetColor(255, 255, 255);
	ofNoFill();
	ofSetLineWidth(5);

	//	ofBezierPoint(p2, p3, p4, p5, 0.0);
	ofBezier(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
	ofBezier(p4.x, p4.y, p5.x, p5.y, p6.x, p6.y, p7.x, p7.y);
}

void BezierSpline::invalidate(void)
{
	reallocate(ofGetWidth(), ofGetHeight());

	setOrigin(poly[40/ 2]);

	drawFboBegin();
	ofSetColor(getFillColor());
	drawSpline();
	drawFboEnd();
}

void BezierSpline::setParam(ofPoint pp1, ofPoint pp2, ofPoint pp3, ofPoint pp4, ofPoint pp5, ofPoint pp6, ofPoint pp7)
{
	p1 = pp1;
	p2 = pp2;
	p3 = pp3;
	p4 = pp4;
	p5 = pp5;
	p6 = pp6;
	p7 = pp7;
}

vector<ofPoint> BezierSpline::getParam()
{
	vector<ofPoint> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);

	return points;
}