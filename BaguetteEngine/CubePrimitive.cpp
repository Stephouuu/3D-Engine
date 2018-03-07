#include "CubePrimitive.hpp"



CubePrimitive::CubePrimitive()
{
	setMesh(box_.getMesh());
	meshType_ = AMesh::CUBE;
}


CubePrimitive::~CubePrimitive()
{
}

void CubePrimitive::setSize(const float width, const float height, const float depth)
{
	box_.set(width, height, depth);
	setMesh(box_.getMesh());
}
