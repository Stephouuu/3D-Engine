#include "ConePrimitive.hpp"

ConePrimitive::ConePrimitive()
{
	setMesh(cone_.getMeshPtr());
	meshType_ = AMesh::CONE;
}

ConePrimitive::~ConePrimitive()
{
}

void ConePrimitive::setSize(const float radius, const float height)
{
	cone_.set(radius, height);
	setMesh(cone_.getMeshPtr());
}

void ConePrimitive::draw_(void)
{
	cone_.draw();
}