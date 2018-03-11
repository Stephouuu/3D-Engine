#include "PlanePrimitive.hpp"

PlanePrimitive::PlanePrimitive()
{
	setMesh(plane_.getMeshPtr());
	meshType_ = AMesh::PLANE;
}


PlanePrimitive::~PlanePrimitive()
{
}

void PlanePrimitive::setSize(const float width, const float height)
{
	plane_.set(width, height);
	setMesh(plane_.getMeshPtr());
}

void PlanePrimitive::draw_(void)
{
	plane_.draw();
}