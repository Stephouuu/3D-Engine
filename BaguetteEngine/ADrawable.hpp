#pragma once

#include "ofNode.h"
#include "ofPoint.h"
#include "Texture.hpp"
#include "IShader.hpp"
#include "BasicShader.hpp"

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

	virtual void setSpecularColor(const ofColor & color);
	virtual ofColor getSpecularColor() const;

	virtual void setDiffuseColor(const ofColor & color);
	virtual ofColor getDiffuseColor() const;

	virtual void invalidate(void) = 0;

	virtual void onPositionChanged(void) override;
	virtual void onOrientationChanged(void) override;
	virtual void onScaleChanged(void) override;

	void setTexture(Texture * texture, int i);
	Texture *getTexture(int i);

	void setShader(const std::string & v, const std::string & f);
	void setShader(IShader *shader);

	void setRotation(float degrees);
	float getRotation(void) const;
	void setFocused(bool v);
	bool isFocused(void) const;
	bool haveOtherShader() const;

protected:
	std::vector<Texture *> textures_;
	IShader				*shader_;
	BasicShader			basicShader_;
	ofColor				specularColor_;
	ofColor				diffuseColor_;
	bool				otherShader_;

private:
	float rotation_;
	bool focused_;
};