#pragma once

#include "Identifiable.hpp"

class IGuiView
{
public:
	virtual ~IGuiView(void) {};
	virtual void draw(void) = 0;
	virtual void setup(void) = 0;
	virtual void refresh(int newEditorDimension) = 0;
	virtual void focus(const Identifiable & id) = 0;
	virtual void windowsResized(const ofPoint & size) = 0;
};