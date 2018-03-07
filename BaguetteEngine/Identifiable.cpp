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

Identifiable::Identifiable(const Identifiable & other)
{
	*this = other;
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

Identifiable & Identifiable::operator=(const Identifiable & other)
{
	setID(other.getID());
	setName(other.getName());
	return *this;
}

bool Identifiable::operator==(const Identifiable & other)
{
	return getID() == other.getID();
}

bool Identifiable::operator!=(const Identifiable & other)
{
	return getID() != other.getID();
}