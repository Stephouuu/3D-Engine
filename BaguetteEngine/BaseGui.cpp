#include "BaseGui.hpp"

BaseGui::BaseGui(SceneController &scene)
	: scene_(scene), editMenu_(scene), sceneViewer_(scene), mainMenu_(scene, editMenu_, sceneViewer_)
{
	scene_.setOnSceneChanged(std::bind(&BaseGui::refresh, this, std::placeholders::_1));
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

void BaseGui::focus(int id)
{
	std::cout << "L'user veut le focus" << std::endl;
}

void BaseGui::refresh(int newEditorDimension)
{
	mainMenu_.refresh(newEditorDimension);
	editMenu_.refresh(newEditorDimension);
	sceneViewer_.refresh(newEditorDimension);
}