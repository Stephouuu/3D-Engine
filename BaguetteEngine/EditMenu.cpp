#include "EditMenu.hpp"



EditMenu::EditMenu(SceneController & scene) : scene_(scene)
{
}

EditMenu::~EditMenu()
{
}

void EditMenu::draw()
{
	gui_.draw();

	//gui_.mouseReleased(mouseEvents_);
	//gui_.mouseEntered(mouseEvents_);
}

void EditMenu::setup()
{

	position_.setName("Positions");
	colorFill_.setName("Couleur");
	size_.setName("Taille");

	//position_.addListener(this, &EditMenu::vecSliderChange);
	//radius_.setName("Rayon"); Pas pour tous

	gui_.setup();
	gui_.setName("Menu d'édition");
	gui_.setPosition(820, 10);

	gui_.add(position_);
	gui_.add(colorFill_);
	gui_.add(size_);
	//gui_.add(radius_);
}

void EditMenu::setFocus(Identifiable & obj)
{
	currentObj_ = scene_.ensureMeshExistance(obj);

	std::cout << obj << std::endl;

	if (currentObj_->getMesh()->getType() == AMesh::InstantiableMesh::SPHERE)
	{

	}
}

void EditMenu::vecSliderChange(const void * sender)
{
//	ofxVecSlider * vec = (ofxVecSlider*)sender;

}
