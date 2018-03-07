#include "Identifiable.hpp"
#include <sstream>

Identifiable::Identifiable(void)
	: id_(0), name_("Default")
{
}

Identifiable::Identifiable(int id)
	: id_(id)
{
	std::ostringstream oss;
	oss << "Object_" << id;
	name_ = oss.str();
}

Identifiable::~Identifiable(void)
{
}

void Identifiable::setID(const int id)
{
	id_ = id;
}

void Identifiable::setName(const std::string & name)
{
	name_ = name;
}

int Identifiable::getID(void) const
{
	return id_;
}

const std::string & Identifiable::getName(void) const
{
	return name_;
}

bool Identifiable::operator==(const Identifiable & other)
{
	return getID() == other.getID();
}

bool Identifiable::operator!=(const Identifiable & other)
{
	return getID() != other.getID();
}