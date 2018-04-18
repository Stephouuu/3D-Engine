#pragma once

#include "AVectorPrimitive.hpp"
#include <vector>

class BezierSpline : public AVectorPrimitive
{
public:
	BezierSpline(void);
	virtual ~BezierSpline(void);
	
	virtual void invalidate(void);

	void setParam(const std::vector<ofPoint> & p);
	const vector<ofPoint> & getParam(void) const;
	void drawSpline(void);

private:
	vector<ofPoint> p_;
};

