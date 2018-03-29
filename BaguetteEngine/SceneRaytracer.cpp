#include "SceneRaytracer.hpp"

SceneRaytracer::SceneRaytracer(void)
	: init_(false)
{
}

SceneRaytracer::~SceneRaytracer(void)
{
}

void SceneRaytracer::render(ARenderer & renderer)
{
	if (!init_) {
		init();
		init_ = true;
	}
	img_.draw(0, 0);
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

void SceneRaytracer::init(void)
{
	int w, h;

	w = ofGetWidth();
	h = ofGetHeight();
	img_.allocate(w, h, ofImageType::OF_IMAGE_COLOR);
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			img_.setColor(x, y, ofColor::yellow);
		}
	}
	img_.update();
}