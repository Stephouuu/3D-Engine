#pragma once

#include "IBasicMeshGenerator.hpp"

class CubeGenerator : IBasicMeshGenerator
{
public:
	CubeGenerator();
	CubeGenerator(const float width, const float height, const float depth);
	AMesh operator()(void) const;
	AMesh generate() const;
	void setSize(const float width, const float height, const float depth);
	void setPosition(const ofVec3f pos);

private:
	ofBoxPrimitive box_;
};