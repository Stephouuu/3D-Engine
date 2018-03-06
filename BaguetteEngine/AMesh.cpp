#include "AMesh.hpp"
#include "ARenderer.hpp"

AMesh::AMesh(void)
{
}

AMesh::~AMesh(void)
{
}

AMesh::AMesh(const ofMesh & oMesh)
{
	vbo_ = oMesh;
}

AMesh AMesh::operator=(const ofMesh & oMesh)
{
	vbo_ = oMesh;
	return *this;
}

void AMesh::setMesh(const ofMesh & oMesh)
{
	vbo_ = oMesh;
}

void AMesh::draw(ARenderer & renderer)
{
	renderer.draw(vbo_);
}