#include "EditMenu.hpp"

EditMenu::EditMenu(SceneController & scene)
	: scene_(scene)
{
}

EditMenu::~EditMenu(void)
{
}

void EditMenu::draw(void)
{
	gui_.draw();

	//gui_.mouseReleased(mouseEvents_);
	//gui_.mouseEntered(mouseEvents_);
}

void EditMenu::setup()
{
	position_.setup("Positions", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	size_.setup("Taille", ofVec3f(1, 1, 1), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	colorFill_.setup("Couleur", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
	rotation_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360));
	baseSetup();
}

void EditMenu::refresh(int newEditorDimension)
{
}

void EditMenu::focus(const Identifiable & id)
{
	SceneNode * node = scene_.ensureDrawableExistance(id);

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

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'edition");
	gui_.setPosition(820, 10);

	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);
	rotation_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderRotationChange);

	gui_.add(&position_);
	gui_.add(&size_);
	gui_.add(&colorFill_);
	gui_.add(&rotation_);
}

void EditMenu::updateValues(SceneNode *node)
{
	// AMesh *currentMesh = dynamic_cast<AMesh *>(currentObj_->getDrawable());
	// AMesh *currentMesh = currentObj_->getMesh();
	IDrawable *currentDrawable = node->getDrawable();

	if (currentDrawable) {
		ofVec3f position = currentDrawable->getPosition();
		position_.setValue(ofVec3f(position.x, position.y, position.z));
		ofVec3f scale = currentDrawable->getScale();
		size_.setValue(ofVec3f(scale.x, scale.y, scale.z));
		ofColor color = currentDrawable->getFillColor();
		colorFill_.setValue(ofColor(color.r, color.g, color.b, color.a));
		ofVec3f rotation = currentDrawable->getOrientationEuler();
		rotation_.setValue(rotation);
	}
	//else {
	//	position_.setValue(ofVec3f(0, 0, 0));
	//	size_.setValue(ofVec3f(1, 1, 1));
	//	colorFill_.setValue(ofColor(0, 0, 0, 255));
	//	rotation_.setValue(ofVec3f(0, 0, 0));
	//}
}

