#pragma once

#include <string>

#include "AScene.hpp"
#include "AMesh.hpp"

#include "SphereGenerator.hpp"
#include "PlaneGenerator.hpp"
#include "CubeGenerator.hpp"
#include "ConeGenerator.hpp"
#include "Model3DGenerator.hpp"

class Scene3D : public AScene
{
public:
	Scene3D(void);
	virtual ~Scene3D(void);
	
	virtual void render(ARenderer & renderer);

	virtual const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	virtual std::string getName(void) const;
	virtual int getNbDimensions(void) const;

private:
	ofEasyCam cam_;
};