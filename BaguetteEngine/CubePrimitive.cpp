#include "CubePrimitive.hpp"
#include "ARenderer.hpp"

CubePrimitive::CubePrimitive()
{
	setMesh(box_.getMeshPtr());
	meshType_ = AMesh::CUBE;
}

CubePrimitive::~CubePrimitive()
{
}

void CubePrimitive::setSize(const float width, const float height, const float depth)
{
	box_.set(width, height, depth);
	setMesh(box_.getMeshPtr());
}

void CubePrimitive::draw_(void)
{
	box_.draw();
}