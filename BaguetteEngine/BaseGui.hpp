#pragma once

#include "MainMenu.hpp"
#include "EditMenu.hpp"

class BaseGui : public IGuiView
{
public:
	BaseGui(SceneController &scene);
	~BaseGui();
	void draw();
	void setup();
	void focus(int id);

private:
	MainMenu			mainMenu_;
	EditMenu			editMenu_;
	SceneController		&scene_;
};
