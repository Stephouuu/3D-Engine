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
	const Identifiable  * obj = scene_.getFocusedMesh();
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
	baseSetup();
}

void EditMenu::setFocus(const Identifiable & obj)
{
	currentObj_ = scene_.ensureMeshExistance(obj);


	if (currentObj_->getMesh()->getType() == AMesh::InstantiableMesh::SPHERE)
	{
		//
	}
	setValues();
	//scene_.setFocusedMesh(obj);
}

void EditMenu::vecSliderPositionChange(ofVec3f & vec)
{
	if (currentObj_ != nullptr)
		scene_.setMeshPosition(static_cast<Identifiable>(*currentObj_), ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderSizeChange(ofVec3f & vec)
{
	if (currentObj_ != nullptr)
		scene_.setMeshScale(static_cast<Identifiable>(*currentObj_), ofVec3f(vec.x, vec.y, vec.z));
}

void EditMenu::vecSliderColorChange(ofColor & color)
{
	if (currentObj_ != nullptr)
	{
		scene_.setMeshColor(static_cast<Identifiable>(*currentObj_), ofFloatColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f));
		std::cout << "Set Color" << color << std::endl;
	}
}

void EditMenu::setValues()
{
	AMesh *currentMesh = currentObj_->getMesh();
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
		//position_.setup("Positions", ofVec3f(position.x, position.y, position.z), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
		ofVec3f scale = currentMesh->getScale();
		//size_.setup("Taille", ofVec3f(scale.x, scale.y, scale.z), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
		size_.setValue(ofVec3f(scale.x, scale.y, scale.z));
		//ofColor color = currentMesh->getColor();
		//colorFill_.setup("Couleur", ofColor(color.r, color.g, color.b, color.a), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
		//baseSetup();
	}
}

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'édition");
	gui_.setPosition(820, 10);

	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);


	gui_.add(&position_);
	gui_.add(&size_);
	gui_.add(&colorFill_);
}
