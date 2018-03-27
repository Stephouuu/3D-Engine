#pragma once

#include "ofNode.h"
#include "ofPoint.h"
#include "Texture.hpp"

class ARenderer;

struct ADrawable : public ofNode
{
public:
	ADrawable(void);
	virtual ~ADrawable(void);

	virtual void destroy(void) = 0;

	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setFillColor(const ofColor & color) = 0;
	virtual const ofColor & getFillColor(void) const = 0;

	virtual void setOutlineColor(const ofColor & color) = 0;
	virtual const ofColor &getOutlineColor(void) const = 0;

	virtual void setOutlineThickness(int thickness) = 0;
	virtual int getOutlineThickness(void) const = 0;

	virtual void invalidate(void) = 0;

	virtual void onPositionChanged(void) override;
	virtual void onOrientationChanged(void) override;
	virtual void onScaleChanged(void) override;

	void setTexture(Texture * texture, int i);
	Texture *getTexture(int i);

	void setShader(const std::string & v, const std::string & f);

	void setRotation(float degrees);
	float getRotation(void) const;
	void setFocused(bool v);
	bool isFocused(void) const;

protected:
	std::vector<Texture *> textures_;
	ofShader shader_;

private:
	float rotation_;
	bool focused_;
};