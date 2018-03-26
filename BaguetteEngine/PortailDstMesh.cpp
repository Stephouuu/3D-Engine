#include "PortailDstMesh.hpp"

PortailDstMesh::PortailDstMesh(void)
{
	plane_.set(1, 1);
	setMesh(plane_.getMeshPtr());
}

PortailDstMesh::~PortailDstMesh(void)
{
}

void PortailDstMesh::setSource(AMesh *src)
{
	src_ = src;
}

void PortailDstMesh::draw_(void)
{

}