#pragma once

class IGuiView
{
public:
	virtual void draw(void) = 0;
	virtual void setup(void) = 0;
	virtual ~IGuiView(void) {};
};