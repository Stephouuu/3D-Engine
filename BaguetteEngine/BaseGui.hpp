#pragma once

#include "MainMenu.hpp"
#include "EditMenu.hpp"
#include "SceneViewer.hpp"

class BaseGui : public IGuiView
{
public:
	BaseGui(SceneController &scene);
	~BaseGui();
	void draw();
	void setup();
	void focus(int id);

private:
	// void refreshGui(void);

private:
	MainMenu			mainMenu_;
	EditMenu			editMenu_;
	SceneViewer			sceneViewer_;
	SceneController		&scene_;
};
