#pragma once

#include "ofMain.h"
#include "MathUtils.hpp"

#include "IDrawable.hpp"

// fix rotation
// screenshot without gui
// radius gui instead of scale
// create more primitives 
class AVectorPrimitive : public IDrawable
{
public:
	enum class Alignment : int {
		Middle = 0
	};

public:
	AVectorPrimitive(void);
	virtual ~AVectorPrimitive(void);

	virtual void update(float dt);
	virtual void draw(ARenderer & renderer);

	virtual void setFillColor(const ofColor & color);
	virtual const ofColor & getFillColor(void) const;

	virtual void setOutlineColor(const ofColor & color);
	virtual const ofColor &getOutlineColor(void) const;

	virtual void setOutlineThickness(int thickness);
	virtual int getOutlineThickness(void) const;

	const ofPoint & getOrigin(void) const;
	void setAlignment(Alignment alignment);
	Alignment getAlignment(void) const;

	/* Invalidate the FBO. Need to be called to display the changes. */
	virtual void invalidate(void) = 0;

protected:
	void setOrigin(const ofPoint & origin);
	
	void reallocate(int w, int h);
	void drawFboBegin(void);
	void drawFboEnd(void);

private:
	ofFbo fbo_;
	ofShader shader_;

	ofColor fillColor_;
	ofColor outlineColor_;
	int outlineThickness_;
	
	// to delete:
	ofVec2f position_;
	float rotation_;
	ofPoint origin_;
	Alignment alignment_;
};

