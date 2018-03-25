#include "AMesh.hpp"
#include "ARenderer.hpp"
#include "ofGraphics.h"

AMesh::AMesh(void)
	: meshType_(UNDEFINED)
{
	mesh_ = nullptr;
	init();
}

AMesh::~AMesh(void)
{
}

void AMesh::draw(ARenderer & renderer)
{
	ofPushMatrix();
		ofTranslate(getGlobalPosition().x, getGlobalPosition().y, getGlobalPosition().z);
		if (isFocused()) ofDrawAxis(std::max({ getScale().x, getScale().y, getScale().z }) + 1);
	ofPopMatrix();

	if (texture()) texture()->getTexture().bind();
	shader_.begin();
		shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
		shader_.setUniform1i("texturePresent", texture() != nullptr);
			mesh_->draw();
	shader_.end();	
	if (texture()) texture()->getTexture().unbind();
}

void AMesh::init(void)
{
	shader_.load("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
}

void AMesh::setVertex(ofIndexType index, const ofVec3f & v)
{
	mesh_->setVertex(index, v);
}

void AMesh::setMesh(ofMesh * oMesh)
{
	mesh_ = oMesh;
	init();
	initColor();
}

const std::vector<ofPoint>& AMesh::getVertices() const
{
	return mesh_->getVertices();
}

ofVec3f AMesh::getVertex(ofIndexType index) const
{
	return mesh_->getVertex(index);
}

void AMesh::setFillColor(const ofColor & c)
{
	if (mesh_)
	{
		const std::vector<ofFloatColor> & vertices = mesh_->getColors();

		for (int i = 0; i < vertices.size(); i++) {
			mesh_->setColor(i, { c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f });
		}
	}
}

const ofColor & AMesh::getFillColor(void) const
{
	return mesh_->getColor(0);
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

void AMesh::setTexture(Texture * texture)
{
	texture_ = texture;
}

void AMesh::invalidate(void)
{
}

void AMesh::initColor(void)
{
	const std::vector<ofPoint> & vertices = mesh_->getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		mesh_->addColor(ofFloatColor::white);
	}
}