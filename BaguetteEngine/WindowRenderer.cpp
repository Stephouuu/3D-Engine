#include "WindowRenderer.hpp"

WindowRenderer::WindowRenderer(void)
{
	create();
}

WindowRenderer::~WindowRenderer(void)
{
}

void WindowRenderer::create(void)
{
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	setFramerate(60);
	ofSetBackgroundColor(63);
}

void WindowRenderer::setFramerate(int fps)
{
	ofSetFrameRate(60);
}

void WindowRenderer::draw(ofVboMesh & vbo)
{
	vbo.draw();
}
