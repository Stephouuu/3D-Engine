#include "AMesh.hpp"
#include "ARenderer.hpp"
#include "ofGraphics.h"

AMesh::AMesh(void)
{
	init();
}

AMesh::~AMesh(void)
{
}

AMesh::AMesh(const ofMesh & oMesh)
{
	init();
	vbo_ = oMesh;
}

AMesh AMesh::operator=(const ofMesh & oMesh)
{
	vbo_ = oMesh;
	return *this;
}

void AMesh::init(void)
{
	shader_.load("./vertex_shader.vert", "./fragment_shader.frag");
	shader_.bindDefaults();
}

void AMesh::setMesh(const ofMesh & oMesh)
{
	vbo_ = oMesh;
}

void AMesh::update(float dt)
{
}

void AMesh::draw(ARenderer & renderer)
{
	shader_.begin();
	shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());

	vbo_.draw();
	
	shader_.end();
}
