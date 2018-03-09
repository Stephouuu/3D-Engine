#include "EditMenu.hpp"



EditMenu::EditMenu(SceneController & scene) : scene_(scene)
{
	currentObj_ = nullptr;
}

EditMenu::~EditMenu()
{
}

void EditMenu::draw()
{
	const Identifiable  * obj = scene_.getFocusedDrawable();
	if (obj != nullptr)
		setFocus(*obj);

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
	std::cerr << "new dimension: " << newEditorDimension << std::endl;
}

void EditMenu::setFocus(const Identifiable & obj)
{
	currentObj_ = scene_.ensureDrawableExistance(obj);

	AMesh *mesh = dynamic_cast<AMesh *>(currentObj_->getDrawable());
	//if (currentObj_->getMesh()->getType() == AMesh::InstantiableMesh::SPHERE)
	if (mesh && mesh->getType() == AMesh::InstantiableMesh::SPHERE)
	{
		//
	}
	setValues();
}

void EditMenu::vecSliderPositionChange(ofVec3f & vec)
{
	if (currentObj_ != nullptr)
		scene_.setDrawablePosition(static_cast<Identifiable>(*currentObj_), ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderSizeChange(ofVec3f & vec)
{
	if (currentObj_ != nullptr)
		scene_.setDrawableScale(static_cast<Identifiable>(*currentObj_), ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderColorChange(ofColor & color)
{
	if (currentObj_ != nullptr)
		scene_.setDrawableColor(static_cast<Identifiable>(*currentObj_), color);
}

void EditMenu::vecSliderRotationChange(ofColor & color)
{
	//if (currentObj_ != nullptr)
	//	scene_.setMeshScale(static_cast<Identifiable>(*currentObj_), ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::setValues()
{
	AMesh *currentMesh = dynamic_cast<AMesh *>(currentObj_->getDrawable());
	// AMesh *currentMesh = currentObj_->getMesh();
	if (currentObj_ == nullptr)
	{
		position_.setValue(ofVec3f(0, 0, 0));
		size_.setValue(ofVec3f(0, 0, 0));
		//setup();
	}
	else
	{
		ofVec3f position = currentMesh->getPosition();
		position_.setValue(ofVec3f(position.x, position.y, position.z));
		ofVec3f scale = currentMesh->getScale();
		size_.setValue(ofVec3f(scale.x, scale.y, scale.z));
		ofColor color = currentMesh->getFillColor();
		colorFill_.setValue(ofColor(color.r, color.g, color.b, color.a));
		//const float roll = currentMesh->getRoll();
		//const float yawl = currentMesh->get
	}
}

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'�dition");
	gui_.setPosition(820, 10);

	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);


	gui_.add(&position_);
	gui_.add(&size_);
	gui_.add(&colorFill_);
	gui_.add(&rotation_);
}
