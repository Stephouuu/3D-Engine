#pragma once

#include "IBasicMeshGenerator.hpp"
#include "ConePrimitive.hpp"

class ConeGenerator : IBasicMeshGenerator
{
public:
	ConeGenerator();
	virtual ~ConeGenerator();
	AMesh operator()(void) const;
	AMesh generate() const;
	void setSize(const float radius, const float height);
	void setPosition(const ofVec3f pos);

private:
	ConePrimitive		cone_;
};

