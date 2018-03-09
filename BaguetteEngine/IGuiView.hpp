#pragma once

class IGuiView
{
public:
	virtual ~IGuiView(void) {};
	virtual void draw(void) = 0;
	virtual void setup(void) = 0;
	virtual void refresh(int newEditorDimension) = 0;
};