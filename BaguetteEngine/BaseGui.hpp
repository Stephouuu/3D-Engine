#pragma once

#include "MainMenu.hpp"

class BaseGui : public IGuiView
{
public:
	BaseGui();
	~BaseGui();
	void draw();
	void setup();
	void buttonPressed(const void * sender);

private:
	MainMenu	mainMenu_;
};
