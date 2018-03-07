#include "BaseGui.hpp"

BaseGui::BaseGui()
{
}


BaseGui::~BaseGui()
{
}

void BaseGui::draw()
{
	ofDisableDepthTest();
	gui_.draw();
	ofEnableDepthTest();
}

void BaseGui::setup()
{	
	fileGroup_.setup();
	fileGroup_.setName("Fichier");
	fileGroup_.add(exportScene_.setup("Exporter la sc�ne"));

	insertGroup_.setup();
	insertGroup_.setName("Ins�rer");
	insertGroup_.add(insertSphere_.setup("Ajouter une sph�re"));

	gui_.setup();
	gui_.setName("Menu");
	gui_.add(&fileGroup_);
	gui_.add(&insertGroup_);

	insertGroup_.minimize();
	fileGroup_.minimize();

	//gui_.add(&insertParam_);
	//gui_.add(insertParam_);
	ofEnableAlphaBlending();
}
