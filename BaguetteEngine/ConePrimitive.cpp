#include "ConePrimitive.hpp"



ConePrimitive::ConePrimitive()
{
	setMesh(cone_.getMesh());
	meshType_ = AMesh::CONE;
}


ConePrimitive::~ConePrimitive()
{
}


void ConePrimitive::setSize(const float radius, const float height)
{
	cone_.set(radius, height);
	setMesh(cone_.getMesh());
}
