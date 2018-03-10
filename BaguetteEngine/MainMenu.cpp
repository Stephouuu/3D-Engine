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
	fileGroup_.add(importImage_.setup("Importer une Image"));

	exportScene_.addListener(this, &MainMenu::buttonPressedFile);
	importImage_.addListener(this, &MainMenu::buttonPressedFile);

	modeGroup_.setup();

	primitiveGroup_.setup();
	model3DGroup_.setup();
	refresh3D();

	insertGroup_.setup();
	insertGroup_.setName("Inserer");
	insertGroup_.add(&model3DGroup_);
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
	model3DGroup_.clear();
	primitiveGroup_.setName("Primitives Vectorielles");
	insertGroup_.clear();

	insertTriangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.removeListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.removeListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);

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

	insertGroup_.setName("Inserer");
	insertGroup_.add(&primitiveGroup_);
	
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
	model3DGroup_.clear();
	model3DGroup_.setName("Modele 3D");
	insertGroup_.clear();

	insertSphere_.removeListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.removeListener(this, &MainMenu::buttonPressed3D);
	insertBox_.removeListener(this, &MainMenu::buttonPressed3D);
	insertCone_.removeListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);

	primitiveGroup_.add(insertSphere_.setup("Ajouter une sphere"));
	primitiveGroup_.add(insertPlan_.setup("Ajouter un plan"));
	primitiveGroup_.add(insertBox_.setup("Ajouter un cube"));
	primitiveGroup_.add(insertCone_.setup("Ajouter un cone"));
	model3DGroup_.add(insert3DModel_.setup("Ajouter un modele 3D"));

	insertSphere_.addListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.addListener(this, &MainMenu::buttonPressed3D);
	insertBox_.addListener(this, &MainMenu::buttonPressed3D);
	insertCone_.addListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.addListener(this, &MainMenu::buttonPressed3DModel);

	insertGroup_.setName("Inserer");
	insertGroup_.add(&model3DGroup_);
	insertGroup_.add(&primitiveGroup_);

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

	else if (button->getName() == "Importer une Image")
	{
		Image uneImage;
		uneImage.Load();
		scene_.AddImage(uneImage);
		editMenu_.setIsImported(true);

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

	if (button->getName() == "Ajouter un triangle")
		scene_.instanciateDrawable("triangle");
	else if (button->getName() == "Ajouter une ellipse")
		scene_.instanciateDrawable("ellipse");
	else if (button->getName() == "Ajouter un point")
		scene_.instanciateDrawable("point");
	else if (button->getName() == "Ajouter un cercle")
		scene_.instanciateDrawable("circle");
	else if (button->getName() == "Ajouter un rectangle")
		scene_.instanciateDrawable("rectangle");
}

void MainMenu::buttonPressed3D(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;
	Identifiable createObj;

	if (button->getName() == "Ajouter une sphere")
		scene_.instanciateDrawable("sphere");
	else if (button->getName() == "Ajouter un plan")
		scene_.instanciateDrawable("plane");
	else if (button->getName() == "Ajouter un cube")
		scene_.instanciateDrawable("cube");
	else if (button->getName() == "Ajouter un cone")
		scene_.instanciateDrawable("cone");
}

void MainMenu::buttonPressed3DModel(const void * sender)
{
	ofxButton	*button = (ofxButton*)sender;
	std::string	path;

	if (button->getName() == "Ajouter un modele 3D")
	{
		ofFileDialogResult result = ofSystemLoadDialog("Load file");
		if (result.bSuccess) {
			path = result.getPath();
			scene_.instanciateDrawable(path);
		}
	}
}
