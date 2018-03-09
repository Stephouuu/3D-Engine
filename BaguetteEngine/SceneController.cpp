#include "SceneController.hpp"
#include "ARenderer.hpp"

SceneController::SceneController(void)
{
	// vector tests
	/* triangle_.setFillColor(ofColor::blue);
	// triangle_.setVerticesPosition({0, 0}, {100, 0}, {100, 80});
	triangle_.setSize(100.f);
	// triangle_.setRotation(45);
	triangle_.setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	// triangle_.setAlignment(AVectorPrimitive::Alignment::Middle);
	triangle_.setOutlineThickness(5);
	triangle_.setOutlineColor(ofColor::red);
	triangle_.invalidate(); */

	scene_ = new Scene3D;
}

SceneController::~SceneController(void)
{
	delete scene_;
}

void SceneController::update(float dt)
{
	scene_->update(dt);
}

void SceneController::render(ARenderer & renderer)
{
	scene_->render(renderer);
	// triangle_.draw(renderer);
}

const Identifiable & SceneController::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	return scene_->instanciateDrawable(type, parent);}

void SceneController::removeDrawable(const Identifiable & drawableId)
{
	scene_->removeDrawable(drawableId);
}

void SceneController::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos)
{
	scene_->setDrawablePosition(drawableId, pos);
}

void SceneController::setDrawableRotation(const Identifiable & drawableId, float degrees, const ofVec3f & axis)
{
	scene_->setDrawableRotation(drawableId, degrees, axis);
}

void SceneController::setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale)
{
	scene_->setDrawableScale(drawableId, scale);
}

void SceneController::setDrawableColor(const Identifiable & drawableId, const ofColor & color)
{
	scene_->setDrawableColor(drawableId, color);
}

void SceneController::graphContent(SceneNode::TreeData & data) const
{
	scene_->graphContent(data);
}

void SceneController::undo(void)
{
	scene_->undo();
}

void SceneController::redo(void)
{
	scene_->redo();
}

void SceneController::setFocusedDrawable(const Identifiable & drawableId)
{
	scene_->setFocusedDrawable(drawableId);
}

const Identifiable * SceneController::getFocusedDrawable(void) const
{
	return scene_->getFocusedDrawable();
}

void SceneController::AddImage(const Image & img)
{
	if (img.isLoaded == true)
		cacheManager.insert(img.path, img.theImg);
	else
		throw std::invalid_argument("Cant insert an empty image.");
}

SceneNode * SceneController::ensureDrawableExistance(const Identifiable & drawableId)
{
	return scene_->ensureDrawableExistance(drawableId);
}