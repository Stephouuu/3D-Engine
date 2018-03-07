#include "EditMenu.hpp"



EditMenu::EditMenu()
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
	radius_.setName("Rayon");
	size_.setName("Taille");

	gui_.setup();
	gui_.setName("Menu d'édition");
	gui_.setPosition(10, 100);

	gui_.add(position_);
	gui_.add(colorFill_);
	gui_.add(size_);
	gui_.add(radius_);
}

void EditMenu::setFocus(const int id)
{

}
