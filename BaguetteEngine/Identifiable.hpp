#pragma once

#include <iostream>

struct Identifiable
{
public:
	Identifiable(void) : id_(0) {}
	Identifiable(int id) : id_(id) {}
	virtual ~Identifiable(void) {}

	virtual int getID(void) const;
	virtual void setID(const int id);

private:
	int id_;
};

inline std::ostream & operator<<(std::ostream & os, const Identifiable & identifiable)
{
	os << identifiable.getID();
	return os;
}