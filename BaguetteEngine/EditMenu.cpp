#include "EditMenu.hpp"

EditMenu::EditMenu(SceneController & scene)
	: scene_(scene), currentDimension_(3), resetting_(false), isImported(false)
{
	scene_.setOnTransformationChanged(std::bind(&EditMenu::onTransformationChange, this));
}

EditMenu::~EditMenu(void)
{
}

void EditMenu::draw(void)
{
	gui_.draw();
	if (isImported) {
		refreshImages();
		isImported = false;
	}
}

void EditMenu::setup()
{
	removeListeners();

	colorFill_.setup("Couleur", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));

	position_.setup("Positions", ofVec3f(0, 0, 0), ofVec3f(-30, -30, -30), ofVec3f(30, 30, 30));
	size_.setup("Taille", ofVec3f(1, 1, 1), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	rotation_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360));

	position2d_.setup("Positions", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));
	size2d_.setup("Taille", ofVec2f(100, 100), ofVec2f(0, 0), ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));
	rotation2d_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(0, 0, 360));

	thickness_.setup("Epaisseur bordure", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(30, 0));
	colorOut_.setup("Couleur bordure", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
	colorScene_.setup("Couleur scene", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));

	baseSetup();
}

void EditMenu::refresh(int newEditorDimension)
{
	currentDimension_ = newEditorDimension;
	gui_.clear();
	ofSetBackgroundColor(scene_.getSceneColor());
	if (newEditorDimension == 2) {
		gui_.add(&position2d_);
		gui_.add(&size2d_);
		gui_.add(&rotation2d_);
		gui_.add(&thickness_);
		gui_.add(&colorOut_);
		gui_.add(&colorScene_);
	}
	else {
		gui_.add(&position_);
		gui_.add(&size_);
		gui_.add(&rotation_);
	}
	gui_.add(&colorFill_);
	gui_.add(&selectTextures_);
}

void EditMenu::refreshImages()
{
	int i = 0;
	images_.clear();
	selectTextures_.clear();
	selectTextures_.setName("Appliquer Images");
	for (auto image = scene_.getCache().getObject().begin(); image != scene_.getCache().getObject().end(); ++image)
	{
		string name = image->first;
		ofxButton *aButton = new ofxButton();
		images_.push_back(aButton->setup(name));
		selectTextures_.add(images_[i]);
		i++;
	}
}

void EditMenu::focus(const Identifiable & id)
{
	SceneNode * node = scene_.ensureDrawableExistance(id);

	if (node) {
		updateValues(node);
	}
}

void EditMenu::windowsResized(const ofPoint & size)
{
	const Identifiable * id = scene_.getFocusedDrawable();

	gui_.clear();
	setup();
	refresh(currentDimension_);
	refreshImages();
	if (id) {
		focus(*id);
	}
	gui_.setPosition(size.x - gui_.getWidth(), 10);
}

void EditMenu::vecSliderPositionChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, vec.z), !resetting_);
}

void EditMenu::vecSliderSizeChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, vec.z), !resetting_);
}

void EditMenu::vecSliderColorChange(ofColor & color)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableColor(*focused, color);
}

void EditMenu::vecSliderRotationChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableRotation(*focused, vec, !resetting_);
}

void EditMenu::vec2SliderPositionChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, 0), !resetting_);
}

void EditMenu::vec2SliderSizeChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, 0), !resetting_);
}

void EditMenu::vec2SliderRotationChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableRotation(*focused, vec.z, !resetting_);
}

void EditMenu::onColorOutChange(ofColor & color)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableOutlineColor(*focused, color);
}

void EditMenu::onThicknessChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableOutlineThickness(*focused, vec.x);
}

void EditMenu::onColorSceneChange(ofColor & color)
{
	scene_.setSceneColor(color);
	ofSetBackgroundColor(color);
}

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'edition");
	gui_.setPosition(820, 10);

	selectTextures_.setup();
	selectTextures_.setName("Appliquer Images");

	initListeners();

	gui_.add(&position_);
	gui_.add(&size_);
	gui_.add(&colorFill_);
	gui_.add(&rotation_);
	gui_.add(&selectTextures_);
}

bool EditMenu::getIsImported()
{
	return isImported;
}

void EditMenu::setIsImported(bool value)
{
	isImported = value;
}

void EditMenu::updateValues(SceneNode *node)
{
	IDrawable *currentDrawable = node->getDrawable();

	resetting_ = true;
	if (currentDimension_ == 3)
	{
		if (currentDrawable) {
			ofVec3f position = currentDrawable->getPosition();
			position_.setValue(ofVec3f(position.x, position.y, position.z));
			ofVec3f scale = currentDrawable->getScale();
			size_.setValue(ofVec3f(scale.x, scale.y, scale.z));
			ofColor color = currentDrawable->getFillColor();
			colorFill_.setValue(ofColor(color.r, color.g, color.b, color.a));
			//const float roll = currentMesh->getRoll();
			//const float yawl = currentMesh->get
		}
		else {
			position_.setValue(ofVec3f(0, 0, 0));
			size_.setValue(ofVec3f(0, 0, 0));
			colorFill_.setValue(ofColor(0, 0, 0, 0));
			//setup();
		}
	}
	else {
		if (currentDrawable) {
			ofVec3f position = currentDrawable->getPosition();
			position2d_.setValue(ofVec2f(position.x, position.y));

			ofVec3f scale = currentDrawable->getScale();
			size2d_.setValue(ofVec2f(scale.x, scale.y));

			ofColor fillColor = currentDrawable->getFillColor();
			colorFill_.setValue(fillColor);

			ofColor outColor = currentDrawable->getOutlineColor();
			colorOut_.setValue(outColor);

			int thickness = currentDrawable->getOutlineThickness();
			thickness_.setValue(ofVec2f(thickness, 0));
		}
		else {
			position2d_.setValue(ofVec2f(0, 0));
			size2d_.setValue(ofVec2f(0, 0));
		}
	}

	ofColor sceneColor = scene_.getSceneColor();
	colorScene_.setValue(sceneColor);
	resetting_ = false;
}

void EditMenu::onTransformationChange(void)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused && focused->getID() > 0) {
		SceneNode * node = scene_.ensureDrawableExistance(*focused);
		updateValues(node);
	}
}

void EditMenu::initListeners(void)
{
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);

	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	rotation_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderRotationChange);

	position2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderPositionChange);
	size2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderSizeChange);
	rotation2d_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vec2SliderRotationChange);

	thickness_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::onThicknessChange);
	colorOut_.getParameter().cast<ofColor>().addListener(this, &EditMenu::onColorOutChange);
	colorScene_.getParameter().cast<ofColor>().addListener(this, &EditMenu::onColorSceneChange);
}

void EditMenu::removeListeners(void)
{
	colorFill_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::vecSliderColorChange);

	position_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderSizeChange);
	rotation_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderRotationChange);

	position2d_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderPositionChange);
	size2d_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderSizeChange);
	rotation2d_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vec2SliderRotationChange);

	thickness_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::onThicknessChange);
	colorOut_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::onColorOutChange);
	colorScene_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::onColorSceneChange);
}