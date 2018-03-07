#pragma once

#include "ofMain.h"
#include "AMesh.hpp"

struct IBasicMeshGenerator
{
	virtual ~IBasicMeshGenerator(void) {}
	virtual AMesh operator()(void) const = 0;
	virtual AMesh generate() const = 0;
};