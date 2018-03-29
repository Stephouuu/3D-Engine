#include "MainMenu.hpp"

MainMenu::MainMenu(SceneController & scene, EditMenu & editMenu, SceneViewer & sceneViewer)
	: scene_(scene), editMenu_(editMenu), sceneViewer_(sceneViewer), wantScreenshot_(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(float dt)
{
}

void MainMenu::draw()
{
	gui_.draw();
}

void MainMenu::setup_(void)
{
	fromXY_.getParameter().cast<ofVec2f>().removeListener(this, &MainMenu::vec2SliderFromXYChange);
	cropWH_.getParameter().cast<ofVec2f>().removeListener(this, &MainMenu::vec2SliderFromWHChange);
	exportScene_.removeListener(this, &MainMenu::buttonPressedFile);
	importImage_.removeListener(this, &MainMenu::buttonPressedFile);
	importCroppedImage_.removeListener(this, &MainMenu::buttonPressedFile);
	fromXY_.getParameter().cast<ofVec2f>().removeListener(this, &MainMenu::vec2SliderFromXYChange);
	cropWH_.getParameter().cast<ofVec2f>().removeListener(this, &MainMenu::vec2SliderFromWHChange);

	fileGroup_.clear();
	fileGroup_.setup();
	fileGroup_.setName("Fichier");
	fileGroup_.add(exportScene_.setup("Exporter la scene"));
	fileGroup_.add(importImage_.setup("Importer une image"));

	cropImage_.clear();
	cropImage_.setup();
	cropImage_.setName("Importer une portion");
	fromXY_.setup("From x/y", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((int)ofGetWidth(), (int)ofGetHeight()));
	cropWH_.setup("Width/Height", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((int)ofGetWidth(), (int)ofGetHeight()));
	cropImage_.add(&fromXY_);
	cropImage_.add(&cropWH_);
	cropImage_.add(importCroppedImage_.setup("Importer Portion"));
	fileGroup_.add(&cropImage_);

	camera_.setup();

	primitiveGroup_.setup();

	model3DGroup_.setup();
	vectorShapeGroup_.setup();

	lightGroup_.setup();

	modeGroup_.setup();
	modeGroup_.setName("Mode");

	insertGroup_.clear();
	insertGroup_.setup();
	insertGroup_.setName("Inserer");

	gui_.clear();
	gui_.setup();
	gui_.setPosition(0, 10);
	gui_.setName("Menu");

	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	vectorShapeGroup_.minimizeAll();
	modeGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
	camera_.minimize();
	vectorShapeGroup_.minimize();
	modeGroup_.minimize();

	fromXY_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::vec2SliderFromXYChange);
	cropWH_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::vec2SliderFromWHChange);
	exportScene_.addListener(this, &MainMenu::buttonPressedFile);
	importImage_.addListener(this, &MainMenu::buttonPressedFile);
	importCroppedImage_.addListener(this, &MainMenu::buttonPressedFile);
	fromXY_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::vec2SliderFromXYChange);
	cropWH_.getParameter().cast<ofVec2f>().addListener(this, &MainMenu::vec2SliderFromWHChange);
}

void MainMenu::setup()
{
	refresh(3);
}

void MainMenu::refresh(int newEditorDimension)
{
	setup_();
	if (newEditorDimension == 2) {
		refresh2D();
	}
	else if (newEditorDimension == 4) {
		refreshRaytracer();
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
	addCamera_.removeListener(this, &MainMenu::addCamera);
	portails_.removeListener(this, &MainMenu::addPortails);
	removeCamera_.removeListener(this, &MainMenu::removeCamera);
	swapCameraMode_.removeListener(this, &MainMenu::toggleSwapMode);
	scene3D_.removeListener(this, &MainMenu::buttonPressedMode);
	scene2D_.removeListener(this, &MainMenu::buttonPressedMode);
	sceneRaytracer_.removeListener(this, &MainMenu::buttonPressedMode);
	insertTriangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.removeListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.removeListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.removeListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.removeListener(this, &MainMenu::buttonPressed2D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().removeListener(this, &MainMenu::vecSliderModel3DBoxChange);
	insertDialogVector_.removeListener(this, &MainMenu::buttonPressedShapeVector);
	insertAmbiantLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertPonctualLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertDirectionalLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertSpotLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertSmileVector_.removeListener(this, &MainMenu::buttonPressedShapeVector);

	primitiveGroup_.setName("Primitives Vectorielles");
	vectorShapeGroup_.setName("Formes Vectorielles");

	modeGroup_.setName("Mode");
	modeGroup_.add(scene3D_.setup("Editeur 3D"));
	modeGroup_.add(sceneRaytracer_.setup("Demo raytracer"));

	primitiveGroup_.add(insertTriangle_.setup("Ajouter un triangle"));
	primitiveGroup_.add(insertEllipse_.setup("Ajouter une ellipse"));
	primitiveGroup_.add(insertPoint_.setup("Ajouter un point"));
	primitiveGroup_.add(insertCircle_.setup("Ajouter un cercle"));
	primitiveGroup_.add(insertRectangle_.setup("Ajouter un rectangle"));

	vectorShapeGroup_.add(insertDialogVector_.setup("Ajouter dialog"));
	vectorShapeGroup_.add(insertSmileVector_.setup("Ajouter smile"));

	insertGroup_.setName("Inserer");
	insertGroup_.add(&primitiveGroup_);
	insertGroup_.add(&vectorShapeGroup_);

	gui_.add(&fileGroup_);
	gui_.add(&modeGroup_);
	gui_.add(&insertGroup_);

	insertGroup_.minimizeAll();
	modeGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
	modeGroup_.minimize();

	scene3D_.addListener(this, &MainMenu::buttonPressedMode);
	sceneRaytracer_.addListener(this, &MainMenu::buttonPressedMode);
	insertTriangle_.addListener(this, &MainMenu::buttonPressed2D);
	insertEllipse_.addListener(this, &MainMenu::buttonPressed2D);
	insertPoint_.addListener(this, &MainMenu::buttonPressed2D);
	insertCircle_.addListener(this, &MainMenu::buttonPressed2D);
	insertRectangle_.addListener(this, &MainMenu::buttonPressed2D);
	insertDialogVector_.addListener(this, &MainMenu::buttonPressedShapeVector);
	insertSmileVector_.addListener(this, &MainMenu::buttonPressedShapeVector);
}

void MainMenu::refresh3D(void)
{
	addCamera_.removeListener(this, &MainMenu::addCamera);
	removeCamera_.removeListener(this, &MainMenu::removeCamera);
	portails_.removeListener(this, &MainMenu::addPortails);
	scene3D_.removeListener(this, &MainMenu::buttonPressedMode);
	scene2D_.removeListener(this, &MainMenu::buttonPressedMode);
	sceneRaytracer_.removeListener(this, &MainMenu::buttonPressedMode);
	swapCameraMode_.removeListener(this, &MainMenu::toggleSwapMode);
	insertSphere_.removeListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.removeListener(this, &MainMenu::buttonPressed3D);
	insertBox_.removeListener(this, &MainMenu::buttonPressed3D);
	insertCone_.removeListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertAmbiantLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertPonctualLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertDirectionalLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertSpotLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().removeListener(this, &MainMenu::vecSliderModel3DBoxChange);

	modeGroup_.setName("Mode");
	modeGroup_.add(scene2D_.setup("Editeur vectoriel"));
	modeGroup_.add(sceneRaytracer_.setup("Demo raytracer"));

	camera_.setName("Camera");
	camera_.add(swapCameraMode_.setup("Mode Ortho/Perspec", false, 20, 20));
	camera_.add(addCamera_.setup("Ajouter camera"));
	camera_.add(removeCamera_.setup("Supprimer camera"));
	camera_.add(portails_.setup("Ajouter portails"));

	primitiveGroup_.setName("Primitives Geometriques");
	model3DGroup_.setName("Modele 3D");
	lightGroup_.setName("Lumieres");

	primitiveGroup_.add(insertSphere_.setup("Ajouter une sphere"));
	primitiveGroup_.add(insertPlan_.setup("Ajouter un plan"));
	primitiveGroup_.add(insertBox_.setup("Ajouter un cube"));
	primitiveGroup_.add(insertCone_.setup("Ajouter un cone"));
	model3DGroup_.add(model3DBoxSlider_.setup("Boite de delimitation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30)));
	model3DGroup_.add(insert3DModel_.setup("Ajouter un modele 3D"));
	lightGroup_.add(insertAmbiantLight_.setup("Lumiere ambiante"));
	lightGroup_.add(insertDirectionalLight_.setup("Lumiere directionelle"));
	lightGroup_.add(insertSpotLight_.setup("Lumiere projecteur"));
	lightGroup_.add(insertPonctualLight_.setup("Lumiere ponctuelle"));

	insertGroup_.setName("Inserer");
	insertGroup_.add(&model3DGroup_);
	insertGroup_.add(&primitiveGroup_);
	insertGroup_.add(&lightGroup_);

	gui_.add(&fileGroup_);
	gui_.add(&modeGroup_);
	gui_.add(&insertGroup_);
	gui_.add(&camera_);

	camera_.minimizeAll();
	insertGroup_.minimizeAll();
	fileGroup_.minimizeAll();
	modeGroup_.minimizeAll();
	insertGroup_.minimize();
	fileGroup_.minimize();
	camera_.minimize();
	modeGroup_.minimize();

	scene2D_.addListener(this, &MainMenu::buttonPressedMode);
	sceneRaytracer_.addListener(this, &MainMenu::buttonPressedMode);
	portails_.addListener(this, &MainMenu::addPortails);
	addCamera_.addListener(this, &MainMenu::addCamera);
	removeCamera_.addListener(this, &MainMenu::removeCamera);
	swapCameraMode_.addListener(this, &MainMenu::toggleSwapMode);
	insertSphere_.addListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.addListener(this, &MainMenu::buttonPressed3D);
	insertBox_.addListener(this, &MainMenu::buttonPressed3D);
	insertCone_.addListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.addListener(this, &MainMenu::buttonPressed3DModel);
	insertAmbiantLight_.addListener(this, &MainMenu::buttonPressed3D);
	insertPonctualLight_.addListener(this, &MainMenu::buttonPressed3D);
	insertDirectionalLight_.addListener(this, &MainMenu::buttonPressed3D);
	insertSpotLight_.addListener(this, &MainMenu::buttonPressed3D);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().addListener(this, &MainMenu::vecSliderModel3DBoxChange);
}

void MainMenu::refreshRaytracer(void)
{
	addCamera_.removeListener(this, &MainMenu::addCamera);
	removeCamera_.removeListener(this, &MainMenu::removeCamera);
	portails_.removeListener(this, &MainMenu::addPortails);
	scene3D_.removeListener(this, &MainMenu::buttonPressedMode);
	scene2D_.removeListener(this, &MainMenu::buttonPressedMode);
	sceneRaytracer_.removeListener(this, &MainMenu::buttonPressedMode);
	swapCameraMode_.removeListener(this, &MainMenu::toggleSwapMode);
	insertSphere_.removeListener(this, &MainMenu::buttonPressed3D);
	insertPlan_.removeListener(this, &MainMenu::buttonPressed3D);
	insertBox_.removeListener(this, &MainMenu::buttonPressed3D);
	insertCone_.removeListener(this, &MainMenu::buttonPressed3D);
	insert3DModel_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertAmbiantLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertPonctualLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertDirectionalLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	insertSpotLight_.removeListener(this, &MainMenu::buttonPressed3DModel);
	model3DBoxSlider_.getParameter().cast<ofVec3f>().removeListener(this, &MainMenu::vecSliderModel3DBoxChange);

	modeGroup_.setName("Mode");
	modeGroup_.add(scene2D_.setup("Editeur vectoriel"));
	modeGroup_.add(scene3D_.setup("Editeur 3D"));

	gui_.add(&modeGroup_);

	modeGroup_.minimize();
	modeGroup_.minimizeAll();

	scene3D_.addListener(this, &MainMenu::buttonPressedMode);
	scene2D_.addListener(this, &MainMenu::buttonPressedMode);
}

void MainMenu::buttonPressedFile(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;

	if (button->getName() == "Exporter la scene") {
		wantScreenshot_ = true;
	}
	else if (button->getName() == "Importer une image") {
		Image uneImage;
		uneImage.Load();
		scene_.addImage(uneImage);
		editMenu_.setIsImported(true);
	}
	else if (button->getName() == "Importer Portion") {
		Image uneImage;
		uneImage.LoadCrop((int)fromXYValues_.x,(int)fromXYValues_.y,(int)cropWHValues_.x,(int)cropWHValues_.y);
		scene_.addImage(uneImage);
		editMenu_.setIsImported(true);
	}
}

void MainMenu::buttonPressedMode(const void * sender)
{
	ofxButton * button = (ofxButton*)sender;

	if (button->getName() == "Editeur vectoriel")
		scene_.setSceneType(SceneController::SceneType::Scene2D);
	else if (button->getName() == "Editeur 3D")
		scene_.setSceneType(SceneController::SceneType::Scene3D);
	else if (button->getName() == "Demo raytracer")
		scene_.setSceneType(SceneController::SceneType::SceneRaytracer);
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
	else if (button->getName() == "Lumiere ambiante")
		scene_.instanciateDrawable("light");
	else if (button->getName() == "Lumiere directionelle")
		scene_.instanciateDrawable("light");
	else if (button->getName() == "Lumiere projecteur")
		scene_.instanciateDrawable("light");
	else if (button->getName() == "Lumiere ponctuelle")
		scene_.instanciateDrawable("light");
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
		scene_.instanciateDrawable("dialog");
	}
	else if (button->getName() == "Ajouter smile") {
		scene_.instanciateDrawable("smile");
	}
}

void MainMenu::vecSliderModel3DBoxChange(ofVec3f & vec)
{
	model3DBox_ = vec;
}

void MainMenu::vec2SliderFromXYChange(ofVec2f & vec)
{
	fromXYValues_ = vec;
}
void MainMenu::vec2SliderFromWHChange(ofVec2f & vec)
{
	cropWHValues_ = vec;
}

void MainMenu::toggleSwapMode(const void * sender, bool & value)
{
	scene_.getCameraController()->swapPerspectiveOrtho(value);
}

void MainMenu::addPortails(const void * sender)
{
	scene_.instanciateDrawable("portails");
}

void MainMenu::addCamera(const void * sender)
{
	scene_.getCameraController()->addCamera();
}

void MainMenu::removeCamera(const void * sender)
{
	scene_.getCameraController()->removeCamera();
}