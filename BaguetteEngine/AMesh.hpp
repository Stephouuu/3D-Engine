#pragma once

#include <vector>
#include "ofMesh.h"
#include "ofNode.h"
#include "ofMain.h"
#include "Identifiable.hpp"
#include "TransformableHistory.hpp"
#include "ADrawable.hpp"
#include "TextureGenerator.hpp"

class ARenderer;

class AMesh : public ADrawable
{
public:
	enum InstantiableMesh
	{
		UNDEFINED,
		MODEL,
		SPHERE,
		PLANE,
		CUBE,
		CONE
	};

public:
	AMesh(void);
	virtual ~AMesh(void);

	virtual void destroy(void) {}

	void init(void);
	const std::vector<ofPoint> & getVertices() const;
	ofVec3f getVertex(ofIndexType index) const;
	void setVertex(ofIndexType index, const ofVec3f & v);
	void setMesh(ofMesh * oMesh);
	void initColor(void);

	virtual void setFillColor(const ofColor & color);
	virtual const ofColor & getFillColor(void) const;

	virtual void setOutlineColor(const ofColor & color);
	virtual const ofColor &getOutlineColor(void) const;

	virtual void setOutlineThickness(int thickness);
	virtual int getOutlineThickness(void) const;

	InstantiableMesh getType(void) const;

	virtual void update(float dt);
	virtual void draw(ARenderer & renderer);

	virtual void invalidate(void);

private:
	virtual void draw_(void) = 0;

private:
	ofMesh * mesh_;

protected:
	InstantiableMesh	meshType_;
};