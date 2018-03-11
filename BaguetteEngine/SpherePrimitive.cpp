#include "SpherePrimitive.hpp"

SpherePrimitive::SpherePrimitive()
{
	setMesh(sphere_.getMeshPtr());
	meshType_ = AMesh::SPHERE;
}


SpherePrimitive::~SpherePrimitive()
{
}

void SpherePrimitive::setRadius(const float radius)
{
	sphere_.setRadius(radius);
	setMesh(sphere_.getMeshPtr());
}

void SpherePrimitive::draw_(void)
{
	sphere_.draw();
}