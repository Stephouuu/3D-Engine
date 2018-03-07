#pragma once

#include <iostream>
#include <string>

struct Identifiable
{
public:
	Identifiable(void);
	Identifiable(int id);
	virtual ~Identifiable(void);

	void setID(const int id);
	void setName(const std::string & name);

	int getID(void) const;
	const std::string & getName(void) const;


	bool operator==(const Identifiable & other);
	bool operator!=(const Identifiable & other);

private:
	int id_;
	std::string name_;
};

inline std::ostream & operator<<(std::ostream & os, const Identifiable & identifiable)
{
	os << identifiable.getID();
	return os;
}