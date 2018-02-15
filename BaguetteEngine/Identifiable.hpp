#pragma once

struct Identifiable
{
	virtual ~Identifiable(void) {}
	virtual int getID(void) const = 0;
};