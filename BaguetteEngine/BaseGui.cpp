#include "BaseGui.hpp"

BaseGui::BaseGui(SceneController &scene)
	: scene_(scene), editMenu_(scene), sceneViewer_(scene), mainMenu_(scene, editMenu_, sceneViewer_)
{
	scene_.setOnSceneChanged(std::bind(&BaseGui::refresh, this, std::placeholders::_1));
	scene_.setOnFocusChanged(std::bind(&BaseGui::focus, this, std::placeholders::_1));
	scene_.setOnImageImported(std::bind(&EditMenu::refreshImages, editMenu_));
}


BaseGui::~BaseGui()
{
}

void BaseGui::draw()
{
	ofDisableDepthTest();
	editMenu_.draw();
	mainMenu_.draw();
	sceneViewer_.draw();
	ofEnableDepthTest();
}

void BaseGui::setup()
{
	ofEnableAlphaBlending();
	mainMenu_.setup();
	editMenu_.setup();
	sceneViewer_.setup();
}

void BaseGui::refresh(int newEditorDimension)
{
	mainMenu_.refresh(newEditorDimension);
	editMenu_.refresh(newEditorDimension);
	sceneViewer_.refresh(newEditorDimension);
}

void BaseGui::focus(const Identifiable & id)
{
	std::cout << "new focused drawable: " << id << std::endl;
	mainMenu_.focus(id);
	editMenu_.focus(id);
	sceneViewer_.focus(id);
}