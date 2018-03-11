#pragma once

#include "AMesh.hpp"

class ConePrimitive : public AMesh
{
public:
	ConePrimitive();
	~ConePrimitive();

	void setSize(const float radius, const float height);

private:
	virtual void draw_(void);

private:
	ofConePrimitive		cone_;
};

