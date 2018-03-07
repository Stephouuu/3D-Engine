#include "MainMenu.hpp"

MainMenu::MainMenu(SceneController & scene, EditMenu & editMenu) : scene_(scene), editMenu_(editMenu)
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	gui_.draw();

	gui_.mouseReleased(mouseEvents_);
	gui_.mouseEntered(mouseEvents_);

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
	primitiveGroup_.add(insertPlan_.setup("Ajouter un plan"));
	primitiveGroup_.add(insertBox_.setup("Ajouter un cube"));
	primitiveGroup_.add(insertCone_.setup("Ajouter un cone"));
	insertSphere_.addListener(this, &MainMenu::buttonPressed);
	insertPlan_.addListener(this, &MainMenu::buttonPressed);
	insertBox_.addListener(this, &MainMenu::buttonPressed);
	insertCone_.addListener(this, &MainMenu::buttonPressed);

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
	Identifiable createObj;

	if (button->getName() == "Ajouter une sphere")
		scene_.instanciateMesh(AMesh::InstantiableMesh::SPHERE);
	else if (button->getName() == "Ajouter un plan")
		scene_.instanciateMesh(AMesh::InstantiableMesh::PLANE);
	else if (button->getName() == "Ajouter un cube")
		scene_.instanciateMesh(AMesh::InstantiableMesh::CUBE);
	else if (button->getName() == "Ajouter un cone")
		scene_.instanciateMesh(AMesh::InstantiableMesh::CONE);
	else
		return;
	editMenu_.setFocus(createObj);
}
