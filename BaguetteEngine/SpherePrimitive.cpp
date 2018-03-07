#include "SpherePrimitive.hpp"

SpherePrimitive::SpherePrimitive()
{
	setMesh(sphere_.getMesh());
	meshType_ = AMesh::SPHERE;
}


SpherePrimitive::~SpherePrimitive()
{
}

void SpherePrimitive::setRadius(const float radius)
{
	sphere_.setRadius(radius);
	setMesh(sphere_.getMesh());
}