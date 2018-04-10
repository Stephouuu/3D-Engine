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
	ofEnableAntiAliasing();
	ofEnableAlphaBlending();
	ofDisableArbTex();
	ofEnableLighting();

	setFramerate(60);
	ofSetBackgroundColor(63);
}

void WindowRenderer::setFramerate(int fps)
{
	ofSetFrameRate(60);
}

void WindowRenderer::draw(const ofVboMesh & vbo)
{
	vbo.draw();
}
