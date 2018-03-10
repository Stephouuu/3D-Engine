#pragma once

#include <vector>
#include "ofMain.h"
#include "Identifiable.hpp"
#include "TransformableHistory.hpp"
#include "IDrawable.hpp"

class ARenderer;

class AMesh : public IDrawable // ofNode
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
	AMesh(const ofMesh & oMesh);
	virtual ~AMesh(void);

	AMesh & operator=(const ofMesh &oMesh);

	void init(void);
	void setMesh(const ofMesh &oMesh);

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
	void initColor(void);

private:
	ofShader			shader_;
	ofVboMesh			vbo_;

protected:
	InstantiableMesh	meshType_;
};