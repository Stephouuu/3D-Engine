#pragma once

#include <vector>
#include "ofMain.h"
#include "Identifiable.hpp"
#include "TransformableHistory.hpp"

class ARenderer;

class AMesh : public ofNode // : public TransformableHistory
{
public:
	enum InstantiableMesh
	{
		UNDEFINED,
		SPHERE,
		PLANE,
		CUBE,
		CONE
	};

public:
	AMesh(void);
	AMesh(const ofMesh & oMesh);
	virtual ~AMesh(void);

	AMesh operator=(const ofMesh &oMesh);

	void init(void);
	void setMesh(const ofMesh &oMesh);
	void setColor(const ofFloatColor & c);
	ofColor getColor(void) const;

	InstantiableMesh getType(void) const;

	void update(float dt);
	virtual void draw(ARenderer & renderer);

private:
	void initColor(void);

private:
	ofShader			shader_;
	ofVboMesh			vbo_;

protected:
	InstantiableMesh	meshType_;
};