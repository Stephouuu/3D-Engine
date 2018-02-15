#pragma once

#include "ARenderer.hpp"

class WindowRenderer : public ARenderer
{
public:
	WindowRenderer(void);
	virtual ~WindowRenderer(void);

	void create(void);
	void setFramerate(int fps);

	virtual void draw(ofVboMesh & vbo);

private:

};