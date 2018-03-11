#pragma once
#include "AMesh.hpp"

class CubePrimitive : public AMesh
{
public:
	CubePrimitive();
	virtual ~CubePrimitive();
	void setSize(const float width, const float height, const float depth);

private:
	void draw_(void);

private:
	ofBoxPrimitive box_;
};

