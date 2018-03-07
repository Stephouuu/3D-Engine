#pragma once

class AIdentifiable
{
	AIdentifiable();
	virtual ~AIdentifiable(void) {}
	virtual int getID(void) const = 0;
};