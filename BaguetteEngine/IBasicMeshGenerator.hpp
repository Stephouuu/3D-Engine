#pragma once

#include "ofMain.h"

class AMesh;

// Maybe useless
struct IBasicMeshGenerator
{
	virtual ~IBasicMeshGenerator(void) {}
	virtual ofMesh operator()(void) const = 0;
	virtual ofMesh generate() const = 0;
};