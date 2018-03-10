#include "MainMenu.hpp"

MainMenu::MainMenu(SceneController & scene, EditMenu & editMenu, SceneViewer & sceneViewer)
	: scene_(scene), editMenu_(editMenu), sceneViewer_(sceneViewer)
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
	exportScene_.addListener(this, &MainMenu::buttonPressedFile);

	modeGroup_.setup();

	primitiveGroup_.setup();
	refresh3D();

	insertGroup_.setup();
	insertGroup_.setName("Inserer");
	insertGroup_.add(&primitiveGroup_);

	gui_.setup();
	gui_.setName("Menu");
	gui_.add(&fileGroup_);
	gui_.add(&modeGroup_);
	gui_.add(&insertGroup_);

	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	modeGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
	modeGroup_.minimize();
}

void MainMenu::refresh(int newEditorDimension)
{
	if (newEditorDimension == 2) {
		refresh2D();
	}
	else {
		refresh3D();
	}
}

void MainMenu::focus(const Identifiable & id)
{
	(void)id;
}

void MainMenu::refresh2D(void)
{
	modeGroup_.clear();
	modeGroup_.setName("Mode");

	swapMode_.removeListener(this, &MainMenu::buttonPressedMode);
	modeGroup_.add(swapMode_.setup("Mode 3D"));
	swapMode_.addListener(this, &MainMenu::buttonPressedMode);
	
	primitiveGroup_.clear();
	primitiveGroup_.setName("Primitives Vectorielles");
	
	insertTriangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.removeListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.removeListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.removeListener(this, &MainMenu::buttonPressed2D);

	primitiveGroup_.add(insertTriangle_.setup("Ajouter un triangle"));
	primitiveGroup_.add(insertEllipse_.setup("Ajouter une ellipse"));
	primitiveGroup_.add(insertPoint_.setup("Ajouter un point"));
	primitiveGroup_.add(insertCircle_.setup("Ajouter un cercle"));
	primitiveGroup_.add(insertRectangle_.setup("Ajouter un rectangle"));

	insertTriangle_.addListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.addListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.addListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.addListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.addListener(this, &MainMenu::buttonPressed2D);
	
	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
}

void MainMenu::refresh3D(void)
{
	modeGroup_.clear();
	modeGroup_.setName("Mode");

	swapMode_.removeListener(this, &MainMenu::buttonPressedMode);
	modeGroup_.add(swapMode_.setup("Mode 2D"));
	swapMode_.addListener(this, &MainMenu::buttonPressedMode);

	primitiveGroup_.clear();
	primitiveGroup_.setName("Primitives Geometriques");

	insertSphere_.removeListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.removeListener(this, &MainMenu::buttonPressed3D);
	insertBox_.removeListener(this, &MainMenu::buttonPressed3D);
	insertCone_.removeListener(this, &MainMenu::buttonPressed3D);

	primitiveGroup_.add(insertSphere_.setup("Ajouter une sphere"));
	primitiveGroup_.add(insertPlan_.setup("Ajouter un plan"));
	primitiveGroup_.add(insertBox_.setup("Ajouter un cube"));
	primitiveGroup_.add(insertCone_.setup("Ajouter un cone"));

	insertSphere_.addListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.addListener(this, &MainMenu::buttonPressed3D);
	insertBox_.addListener(this, &MainMenu::buttonPressed3D);
	insertCone_.addListener(this, &MainMenu::buttonPressed3D);

	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
}

void MainMenu::buttonPressedFile(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;

	if (button->getName() == "Exporter la scene")
	{
		exportImg_.Export("screenshot");
		return;
	}
}

void MainMenu::buttonPressedMode(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;

	if (button->getName() == "Mode 2D" || button->getName() == "Mode 3D")
		scene_.swapMode();
}

void MainMenu::buttonPressed2D(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;
	Identifiable createObj;

	if (button->getName() == "Ajouter un triangle")
		createObj = scene_.instanciateDrawable("triangle");
	else if (button->getName() == "Ajouter une ellipse")
		createObj = scene_.instanciateDrawable("ellipse");
	else if (button->getName() == "Ajouter un point")
		createObj = scene_.instanciateDrawable("point");
	else if (button->getName() == "Ajouter un cercle")
		createObj = scene_.instanciateDrawable("circle");
	else if (button->getName() == "Ajouter un rectangle")
		createObj = scene_.instanciateDrawable("rectangle");
}

void MainMenu::buttonPressed3D(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;
	Identifiable createObj;

	if (button->getName() == "Ajouter une sphere")
		createObj = scene_.instanciateDrawable("sphere");
	else if (button->getName() == "Ajouter un plan")
		createObj = scene_.instanciateDrawable("plane");
	else if (button->getName() == "Ajouter un cube")
		createObj = scene_.instanciateDrawable("cube");
	else if (button->getName() == "Ajouter un cone")
		createObj = scene_.instanciateDrawable("cone");
}