#include "MainMenu.hpp"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	gui_.draw();
}

void MainMenu::setup()
{
	fileGroup_.setup();
	fileGroup_.setName("Fichier");
	fileGroup_.add(exportScene_.setup("Exporter la scene"));
	exportScene_.addListener(this, &MainMenu::buttonPressed);

	primitiveGroup_.setup();
	primitiveGroup_.setName("Primitives Géométriques");
	primitiveGroup_.add(insertSphere_.setup("Ajouter une sphere"));
	insertSphere_.addListener(this, &MainMenu::buttonPressed);

	insertGroup_.setup();
	insertGroup_.setName("Inserer");
	insertGroup_.add(&primitiveGroup_);

	gui_.setup();
	gui_.setName("Menu");
	gui_.add(&fileGroup_);
	gui_.add(&insertGroup_);

	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
}

void MainMenu::buttonPressed(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;
	button->getName();
	std::cout << "click on " << button->getName() << std::endl;;
}
