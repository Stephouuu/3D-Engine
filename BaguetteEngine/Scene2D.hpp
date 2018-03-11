#pragma once

#include "AScene.hpp"
#include "AVectorPrimitive.hpp"

#include "TriangleVector.hpp"
#include "EllipseVector.hpp"
#include "PointVector.hpp"
#include "RectangleVector.hpp"

#include "DialogVectorShape.hpp"

class Scene2D : public AScene
{
public:
	Scene2D(void);
	virtual ~Scene2D(void);

	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	virtual std::string getName(void) const;
	virtual int getNbDimensions(void) const;
};

