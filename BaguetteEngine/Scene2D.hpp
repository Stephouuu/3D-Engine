#pragma once

#include "AScene.hpp"
#include "AVectorPrimitive.hpp"

#include "TriangleVector.hpp"

class Scene2D : public AScene
{
public:
	Scene2D(void);
	virtual ~Scene2D(void);

	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	virtual int getNbDimensions(void) const;

private:
	// background scene color
};

