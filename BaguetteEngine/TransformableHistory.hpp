#pragma once

#include <list>

#include "ofMain.h"
#include "Identifiable.hpp"

class TransformableHistory // : public ofNode
{
public:
	typedef std::pair<Identifiable, ofMatrix4x4> Item;

public:
	TransformableHistory(void);
	virtual ~TransformableHistory(void);

	const Item & undo(void);
	const Item & redo(void);

	void deleteTransformations(const Identifiable & id);
	void pushTransformation(const Item & t);

private:
	static const int MAX_HISTORY = 10;

private:
	std::list<Item> historic_;
	std::list<Item>::const_iterator current_;
};

