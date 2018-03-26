#pragma once

/* FBO */

#include "ARenderer.hpp"

class TextureRenderer : public ARenderer
{
public:
	TextureRenderer(void);
	virtual ~TextureRenderer(void);


	virtual void draw(const ofVboMesh & vbo);

private:

};