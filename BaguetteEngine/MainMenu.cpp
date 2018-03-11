#include "MainMenu.hpp"

MainMenu::MainMenu(SceneController & scene, EditMenu & editMenu, SceneViewer & sceneViewer)
	: scene_(scene), editMenu_(editMenu), sceneViewer_(sceneViewer), wantScreenshot_(false)
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
	fileGroup_.add(importImage_.setup("Importer une Image"));
	cropImage_.setup();
	cropImage_.setName("Importer une portion d'IMG");
	fromXY_.setup("From x/y", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((int)ofGetWidth(), (int)ofGetHeight()));
	cropWH_.setup("Width/Height", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((int)ofGetWidth(), (int)ofGetHeight()));


	cropImage_.add(&fromXY_);
	cropImage_.add(&cropWH_);
	cropImage_.add(importCroppedImage_.setup("Importer Portion"));
	fileGroup_.add(&cropImage_);

	fromXY_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::setFromXYValues);
	cropWH_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::setFromWHValues);
	exportScene_.addListener(this, &MainMenu::buttonPressedFile);
	importImage_.addListener(this, &MainMenu::buttonPressedFile);
	importCroppedImage_.addListener(this, &MainMenu::buttonPressedFile);

	modeGroup_.setup();

	primitiveGroup_.setup();
	model3DGroup_.setup();
	vectorShapeGroup_.setup();

	refresh3D();

	insertGroup_.setup();
	insertGroup_.setName("Inserer");
	insertGroup_.add(&model3DGroup_);
	insertGroup_.add(&primitiveGroup_);

	gui_.setup();
	gui_.setPosition(0, 10);
	gui_.setName("Menu");
	gui_.add(&fileGroup_);
	gui_.add(&modeGroup_);
	gui_.add(&insertGroup_);

	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	modeGroup_.minimizeAll();
	vectorShapeGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
	modeGroup_.minimize();
	vectorShapeGroup_.maximize();
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

void MainMenu::windowsResized(const ofPoint & size)
{
}

bool MainMenu::wantScreenshot(void)
{
	bool tmp = wantScreenshot_;
	if (tmp) {
		wantScreenshot_ = false;
	}
	return tmp;
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
	insertGroup_.clear();
	vectorShapeGroup_.clear();

	primitiveGroup_.setName("Primitives Vectorielles");
	vectorShapeGroup_.setName("Formes Vectorielles");

	insertTriangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.removeListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.removeListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().removeListener(this, &MainMenu::vecSliderModel3DBoxChange);
	insertDialogVector_.removeListener(this, &MainMenu::buttonPressedShapeVector);

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
	insertDialogVector_.addListener(this, &MainMenu::buttonPressedShapeVector);

	vectorShapeGroup_.add(insertDialogVector_.setup("Ajouter dialog"));

	insertGroup_.setName("Inserer");
	insertGroup_.add(&primitiveGroup_);
	insertGroup_.add(&vectorShapeGroup_);
	
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
	model3DBoxSlider_.getParameter().cast<ofVec3f>().removeListener(this, &MainMenu::vecSliderModel3DBoxChange);

	primitiveGroup_.add(insertSphere_.setup("Ajouter une sphere"));
	primitiveGroup_.add(insertPlan_.setup("Ajouter un plan"));
	primitiveGroup_.add(insertBox_.setup("Ajouter un cube"));
	primitiveGroup_.add(insertCone_.setup("Ajouter un cone"));
	model3DGroup_.add(model3DBoxSlider_.setup("Boite de delimitation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30)));
	model3DGroup_.add(insert3DModel_.setup("Ajouter un modele 3D"));

	insertSphere_.addListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.addListener(this, &MainMenu::buttonPressed3D);
	insertBox_.addListener(this, &MainMenu::buttonPressed3D);
	insertCone_.addListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.addListener(this, &MainMenu::buttonPressed3DModel);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().addListener(this, &MainMenu::vecSliderModel3DBoxChange);

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

	if (button->getName() == "Exporter la scene") {
		wantScreenshot_ = true;
	}
	else if (button->getName() == "Importer une Image") {
		Image uneImage;
		uneImage.Load();
		scene_.addImage(uneImage);
		editMenu_.setIsImported(true);
	}
	else if (button->getName() == "Importer Portion") {
		std::cout << "bonjour" << std::endl;
		Image uneImage;
		uneImage.LoadCrop((int)fromXYValues_.x,(int)fromXYValues_.y,(int)fromWHValues_.x,(int)fromWHValues_.y);
		scene_.addImage(uneImage);
		editMenu_.setIsImported(true);
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
	ofxButton		*button = (ofxButton*)sender;
	std::string		path;
	Identifiable	createdObj;
	AMesh			*createdMesh;
	ofPoint			max(0, 0, 0);


	if (button->getName() == "Ajouter un modele 3D")
	{
		ofFileDialogResult	result = ofSystemLoadDialog("Load file");
		size_t				index = 0;

		if (result.bSuccess) {
			path = result.getPath();
			createdObj = scene_.instanciateDrawable(path);

			if (model3DBox_ == ofPoint(0, 0, 0))
				return;

			createdMesh = dynamic_cast<AMesh*>(scene_.ensureDrawableExistance(createdObj)->getDrawable());

			const std::vector<ofPoint> & vertices = createdMesh->getVertices();
			std::vector<ofPoint>::const_iterator it;
			for (it = vertices.begin(); it != vertices.end(); it++)
			{
				max.x = std::max(it->x, max.x);
				max.y = std::max(it->y, max.y);
				max.z = std::max(it->z, max.z);
			}

			model3DBox_.x /= 2;
			model3DBox_.y /= 2;
			model3DBox_.z /= 2;

			ofPoint ratio(model3DBox_.x / max.x, model3DBox_.y / max.y, model3DBox_.z / max.z);

			for (it = vertices.begin(); it != vertices.end(); it++)
			{				
				createdMesh->setVertex(index, ofVec3f(it->x * ratio.x, it->y * ratio.y, it->z * ratio.z));
				index++;
			}
			scene_.setFocusedDrawable(0);
			scene_.setFocusedDrawable(createdObj);
		}
	}
}

void MainMenu::buttonPressedShapeVector(const void * sender)
{
	ofxButton		*button = (ofxButton*)sender;

	if (button->getName() == "Ajouter dialog") {
		std::cerr << "ajouter dialog" << std::endl;
		scene_.instanciateDrawable("dialog");
	}
}

void MainMenu::vecSliderModel3DBoxChange(ofVec3f & vec)
{
	model3DBox_ = vec;
}

void MainMenu::setFromXYValues(ofVec2f & vec)
{
	fromXYValues_ = vec;
}

void MainMenu::setFromWHValues(ofVec2f & vec)
{
	fromWHValues_ = vec;
}