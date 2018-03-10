#include "EditMenu.hpp"

EditMenu::EditMenu(SceneController & scene)
	: scene_(scene), currentDimension_(3), isImported(false)
{
}

EditMenu::~EditMenu(void)
{
}

void EditMenu::draw(void)
{
	gui_.draw();
	if (isImported) {
		refreshImages();
		// scene_.refreshImage();
		isImported = false;
	}
	//gui_.mouseReleased(mouseEvents_);
	//gui_.mouseEntered(mouseEvents_);
}

void EditMenu::setup()
{
	colorFill_.setup("Couleur", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));

	position_.setup("Positions", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	size_.setup("Taille", ofVec3f(1, 1, 1), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	rotation_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360));

	position2d_.setup("Positions", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));
	size2d_.setup("Taille", ofVec2f(100, 100), ofVec2f(0, 0), ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));
	rotation2d_.setup("Rotation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(360, 360));

	baseSetup();
}

void EditMenu::refresh(int newEditorDimension)
{
	currentDimension_ = newEditorDimension;
	gui_.clear();
	if (newEditorDimension == 2) {
		gui_.add(&position2d_);
		gui_.add(&size2d_);
		gui_.add(&rotation2d_);
	}
	else {
		gui_.add(&position_);
		gui_.add(&size_);
		gui_.add(&rotation_);
	}
	gui_.add(&colorFill_);
}

void EditMenu::refreshImages()
{
	int i = 0;
	images_.clear();
	selectTextures_.clear();
	selectTextures_.setName("Appliquer Images");
	for (auto image = scene_.getCache().getObject().begin(); image != scene_.getCache().getObject().end(); ++image)
	{
		//std::size_t found = image->first.find_last_of("/\\");
		//string name = image->first.substr(found + 1);
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

	std::cerr << "new focus: " << id << std::endl;
	if (node) {
		updateValues(node);
	}
}

void EditMenu::vecSliderPositionChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderSizeChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderColorChange(ofColor & color)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableColor(*focused, color);
}

void EditMenu::vecSliderRotationChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableRotation(*focused, vec);
}

void EditMenu::vec2SliderPositionChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, 0));
}

void EditMenu::vec2SliderSizeChange(ofVec2f & vec)
{
	std::cout << "slide change" << std::endl;
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, 0));
}

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'edition");
	gui_.setPosition(820, 10);

	selectTextures_.setup();
	selectTextures_.setName("Appliquer Images");


	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);
	rotation_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderRotationChange);

	position2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderPositionChange);
	size2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderSizeChange);

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
	// AMesh *currentMesh = dynamic_cast<AMesh *>(currentObj_->getDrawable());
	// AMesh *currentMesh = currentObj_->getMesh();
	IDrawable *currentDrawable = node->getDrawable();

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
			//setup();
		}
	}
	else {
		if (currentDrawable) {
			ofVec3f position = currentDrawable->getPosition();
			position2d_.setValue(ofVec2f(position.x, position.y));
			ofVec3f scale = currentDrawable->getScale();
			size2d_.setValue(ofVec2f(scale.x, scale.y));
			ofColor color = currentDrawable->getFillColor();
			colorFill_.setValue(ofColor(color.r, color.g, color.b, color.a));
		}
		else {
			position2d_.setValue(ofVec2f(0, 0));
			size2d_.setValue(ofVec2f(0, 0));
		}
	}
}

