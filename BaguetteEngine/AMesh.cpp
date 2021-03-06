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
	bool texturePresent = !textures_.empty();

	ofPushMatrix();
		ofTranslate(getGlobalPosition().x, getGlobalPosition().y, getGlobalPosition().z);
		if (isFocused()) ofDrawAxis(std::max({ getScale().x, getScale().y, getScale().z }) + 1);
	ofPopMatrix();

	if (otherShader_ || texturePresent)
	{
		basicShader_.begin();
		basicShader_.setUniform1i("texturePresent", texturePresent);
		basicShader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
		for (int i = 0; i < textures_.size(); ++i)
			basicShader_.setUniformTexture("tex" + std::to_string(i), textures_[i]->getTexture(), i);
		draw_();
		basicShader_.end();
	}
	else
	{
		if (shader_ == nullptr)
		{
			draw_();
			return;
		}
		shader_->begin();
		shader_->setUniform1i("texturePresent", texturePresent);

		LightShader *lightShader;
		lightShader = dynamic_cast<LightShader*>(shader_);
		lightShader->setSpecularMaterial(specularColor_);
		lightShader->setDiffuseMaterial(diffuseColor_);

		shader_->setUniformMatrix4f("model", getGlobalTransformMatrix());
		for (int i = 0; i < textures_.size(); ++i)
			shader_->setUniformTexture("tex" + std::to_string(i), textures_[i]->getTexture(), i);
		draw_();
		shader_->end();
	}
}

void AMesh::init(void)
{
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