#pragma once
#include "AMesh.hpp"

class CubePrimitive : public AMesh
{
public:
	CubePrimitive(void);
	virtual ~CubePrimitive(void);
	void setSize(const float width, const float height, const float depth);

private:
	virtual void draw_(void);

private:
	ofBoxPrimitive box_;
};

