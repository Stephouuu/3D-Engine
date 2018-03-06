#pragma once

class AMesh;

// Maybe useless
struct IBasicMeshGenerator
{
	virtual ~IBasicMeshGenerator(void) {}
	virtual AMesh operator()(void) const = 0;
	virtual AMesh generate() const = 0;
};