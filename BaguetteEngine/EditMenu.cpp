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

	gui_.mouseReleased(mouseEvents_);
	gui_.mouseEntered(mouseEvents_);
}

void EditMenu::setup()
{
	positiontGroup_.setup();
	positiontGroup_.setName("Positions");

	colorGroup_.setup();
	colorGroup_.setName("Couleurs");

	gui_.setup();
	gui_.mouseReleased(mouseEvents_);
	gui_.setName("Menu d'édition");
	gui_.setPosition(10, 100);

	gui_.add(&positiontGroup_);
	gui_.add(&colorGroup_);
}
