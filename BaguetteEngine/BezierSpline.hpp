#pragma once
#include "AVectorPrimitive.hpp"
#include <vector>

class BezierSpline : public AVectorPrimitive
{
public:
	BezierSpline(void);
	virtual ~BezierSpline(void);
	virtual void invalidate(void);
	virtual void setParam(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4, ofPoint p5, ofPoint p6, ofPoint p7);
	vector<ofPoint> getParam();
	void drawSpline();
private:
	ofPolyline poly;
	ofPoint p1;
	ofPoint p2;
	ofPoint p3;
	ofPoint p4;
	ofPoint p5;
	ofPoint p6;
	ofPoint p7;
	vector<ofPoint> pointVector;
};

