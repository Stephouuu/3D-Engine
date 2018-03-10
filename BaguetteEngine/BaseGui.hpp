#pragma once

#include "MainMenu.hpp"
#include "EditMenu.hpp"
#include "SceneViewer.hpp"

class BaseGui : public IGuiView
{
public:
	BaseGui(SceneController &scene);
	virtual ~BaseGui();

	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);
	virtual void focus(const Identifiable & id);

	virtual void windowsResized(const ofPoint & size);

private:
	MainMenu			mainMenu_;
	EditMenu			editMenu_;
	SceneViewer			sceneViewer_;
	SceneController		&scene_;
};
