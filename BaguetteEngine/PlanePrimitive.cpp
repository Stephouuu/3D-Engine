#include "PlanePrimitive.hpp"



PlanePrimitive::PlanePrimitive()
{
	setMesh(plane_.getMesh());
	meshType_ = AMesh::PLANE;
}


PlanePrimitive::~PlanePrimitive()
{
}

void PlanePrimitive::setSize(const float width, const float height)
{
	plane_.set(width, height);
	setMesh(plane_.getMesh());
}
