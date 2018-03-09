#pragma once

#include "ofMain.h"
#include "MathUtils.hpp"

class AVectorPrimitive
{
public:
	enum class Alignment : int {
		Middle = 0
	};

public:
	AVectorPrimitive(void);
	virtual ~AVectorPrimitive(void);

	void draw(void);

	void setPosition(const ofVec2f & position);
	const ofVec2f & getPosition(void) const;

	void setRotation(float angle);
	float getRotation(void) const;

	void setFillColor(const ofColor & color);
	const ofColor & getFillColor(void) const;

	void setOutlineColor(const ofColor & color);
	const ofColor & getOutlineColor(void) const;

	void setOutlineThickness(int thickness);
	int getOutlineThickness(void) const;

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
	ofColor fillColor_;
	ofColor outlineColor_;
	int outlineThickness_;
	ofVec2f position_;
	float rotation_;
	ofPoint origin_;
	Alignment alignment_;
};

