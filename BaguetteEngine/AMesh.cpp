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
	setMesh(oMesh);
}

AMesh AMesh::operator=(const ofMesh & oMesh)
{
	setMesh(oMesh);
	return *this;
}

void AMesh::init(void)
{
	shader_.load("./vertex_shader.vert", "./fragment_shader.frag");
	shader_.bindDefaults();
	meshType_ = InstantiableMesh::UNDEFINED;
}

void AMesh::setMesh(const ofMesh & oMesh)
{
	vbo_ = oMesh;
	init();
	initColor();
}

void AMesh::setColor(const ofFloatColor & c)
{
	const std::vector<ofPoint> & vertices = vbo_.getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		vbo_.setColor(i, c);
	}
}

AMesh::InstantiableMesh AMesh::getType(void) const
{
	return meshType_;
}

void AMesh::update(float dt)
{
}

void AMesh::draw(ARenderer & renderer)
{
	shader_.begin();
	shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());

	renderer.draw(vbo_);
	
	shader_.end();
}

void AMesh::initColor(void)
{
	const std::vector<ofPoint> & vertices = vbo_.getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		vbo_.addColor(ofFloatColor::white);
	}
}