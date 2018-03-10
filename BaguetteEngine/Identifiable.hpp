#pragma once

#include <iostream>
#include <string>

struct Identifiable
{
public:
	Identifiable(void);
	Identifiable(int id);
	Identifiable(const Identifiable & other);
	virtual ~Identifiable(void);

	void setID(const int id);
	void setName(const std::string & name);

	int getID(void) const;
	const std::string & getName(void) const;

	Identifiable & operator=(const Identifiable & other);

private:
	int id_;
	std::string name_;
};

inline std::ostream & operator<<(std::ostream & os, const Identifiable & identifiable)
{
	os << identifiable.getID();
	return os;
}

inline bool operator==(const Identifiable & lhs, const Identifiable & rhs)
{
	return lhs.getID() == rhs.getID();
}

inline bool operator==(const Identifiable & lhs, const Identifiable * rhs)
{
	return lhs.getID() == rhs->getID();
}

inline bool operator==(const Identifiable & lhs, int rhs)
{
	return lhs.getID() == rhs;
}

inline bool operator!=(const Identifiable & lhs, const Identifiable & rhs)
{
	return lhs.getID() != rhs.getID();
}

inline bool operator!=(const Identifiable & lhs, const Identifiable * rhs)
{
	return lhs.getID() != rhs->getID();
}

inline bool operator!=(const Identifiable & lhs, int rhs)
{
	return lhs.getID() != rhs;
}