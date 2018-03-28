#include "SceneRaytracer.hpp"

SceneRaytracer::SceneRaytracer(void)
{
}

SceneRaytracer::~SceneRaytracer(void)
{
}

void SceneRaytracer::render(ARenderer & renderer)
{

}

const Identifiable & SceneRaytracer::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	throw std::runtime_error("SceneRaytracer::instanciateDrawable: not yet implemented");
}

std::string SceneRaytracer::getName(void) const
{
	return "Raytracer";
}

int SceneRaytracer::getNbDimensions(void) const
{
	return 4;
}

CameraController & SceneRaytracer::getCameraController(void)
{
	return cc_;
}