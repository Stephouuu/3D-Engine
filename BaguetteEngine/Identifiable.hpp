#pragma once

struct Identifiable
{
public:
	virtual ~Identifiable(void) {}
	virtual int getID(void) const;
	virtual void setID(const int id);

private:
	int			id_;
};