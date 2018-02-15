#include "AMesh.hpp"
#include "ARenderer.hpp"

AMesh::AMesh(void)
{
	// vbo => vertex buffer object
	vbo_.addVertex(ofPoint(0, 0, 0));
	vbo_.addVertex(ofPoint(1, 0, 0));
	vbo_.addVertex(ofPoint(0, 1, 0));

	vbo_.addColor(ofColor(255, 0, 0, 255));
	vbo_.addColor(ofColor(255, 0, 0, 255));
	vbo_.addColor(ofColor(255, 0, 0, 255));
}

AMesh::~AMesh(void)
{
}

void AMesh::draw(ARenderer & renderer)
{
	renderer.draw(vbo_);
}