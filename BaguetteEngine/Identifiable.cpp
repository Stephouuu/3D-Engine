#include "Identifiable.hpp"

int Identifiable::getID(void) const
{
	return id_;
}

void Identifiable::setID(const int id)
{
	id_ = id;
}
