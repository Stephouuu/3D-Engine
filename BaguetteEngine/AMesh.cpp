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

AMesh & AMesh::operator=(const ofMesh & oMesh)
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

void AMesh::setFillColor(const ofColor & c)
{
	const std::vector<ofPoint> & vertices = vbo_.getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		vbo_.setColor(i, { c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f });
	}
}

const ofColor & AMesh::getFillColor(void) const
{
	return vbo_.getColor(0);
}

void AMesh::setOutlineColor(const ofColor & color)
{
}

const ofColor & AMesh::getOutlineColor(void) const
{
	return getFillColor();
}

void AMesh::setOutlineThickness(int thickness)
{
}

int AMesh::getOutlineThickness(void) const
{
	return 0;
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
	ofPushMatrix();
		ofTranslate(getGlobalPosition().x, getGlobalPosition().y, getGlobalPosition().z);
		if (isFocused()) ofDrawAxis(std::max({ getScale().x, getScale().y, getScale().z }) + 1);
	ofPopMatrix();
	shader_.begin();
		shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
		renderer.draw(vbo_);
	shader_.end();
}

void AMesh::invalidate(void)
{
}

void AMesh::initColor(void)
{
	const std::vector<ofPoint> & vertices = vbo_.getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		vbo_.addColor(ofFloatColor::white);
	}
}