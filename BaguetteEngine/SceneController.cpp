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

	scenes_.emplace_back(new Scene3D);
	scenes_.emplace_back(new Scene2D);
	currentScene_ = std::begin(scenes_);
	ofSetWindowTitle((*currentScene_)->getName());
}

SceneController::~SceneController(void)
{
}

void SceneController::swapMode(void)
{
	currentScene_++;
	if (currentScene_ == std::end(scenes_)) {
		currentScene_ = std::begin(scenes_);
	}
	if (onSceneChanged_) onSceneChanged_((*currentScene_)->getNbDimensions());
	if (onGraphSceneChanged_) onGraphSceneChanged_();

	ofSetWindowTitle((*currentScene_)->getName());
}

void SceneController::setOnSceneChanged(std::function<void(int)> callback)
{
	onSceneChanged_ = callback;
}

void SceneController::setOnGraphSceneChanged(std::function<void(void)> callback)
{
	onGraphSceneChanged_ = callback;
}

void SceneController::setOnFocusChanged(std::function<void(const Identifiable &)> callback)
{
	onFocusChanged_ = callback;
}

void SceneController::update(float dt)
{
	(*currentScene_)->update(dt);
}

void SceneController::render(ARenderer & renderer)
{
	(*currentScene_)->render(renderer);
}

const Identifiable & SceneController::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	try {
		const Identifiable & id = (*currentScene_)->instanciateDrawable(type, parent);
		setFocusedDrawable(id);
		onGraphSceneChanged_();
		return id;
	}
	catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
	}
}

void SceneController::removeDrawable(const Identifiable & drawableId)
{
	(*currentScene_)->removeDrawable(drawableId);
}

void SceneController::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos)
{
	(*currentScene_)->setDrawablePosition(drawableId, pos);
}

void SceneController::setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation)
{
	(*currentScene_)->setDrawableRotation(drawableId, orientation);
}

void SceneController::setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale)
{
	(*currentScene_)->setDrawableScale(drawableId, scale);
}

void SceneController::setDrawableColor(const Identifiable & drawableId, const ofColor & color)
{
	(*currentScene_)->setDrawableColor(drawableId, color);
}

void SceneController::setDrawableOutlineColor(const Identifiable & drawableId, const ofColor & color)
{
	(*currentScene_)->setDrawableOutlineColor(drawableId, color);
}

void SceneController::setDrawableOutlineThickness(const Identifiable & drawableId, int thickness)
{
	(*currentScene_)->setDrawableOutlineThickness(drawableId, thickness);
}

void SceneController::graphContent(SceneNode::TreeData & data) const
{
	(*currentScene_)->graphContent(data);
}

void SceneController::undo(void)
{
	(*currentScene_)->undo();
}

void SceneController::redo(void)
{
	(*currentScene_)->redo();
}

void SceneController::setFocusedDrawable(const Identifiable & drawableId)
{	
	const Identifiable * currentFocus = getFocusedDrawable();

	if (currentFocus && currentFocus->getID() != drawableId.getID()) {
		(*currentScene_)->setFocusedDrawable(drawableId);
		if (onFocusChanged_) onFocusChanged_(drawableId);
	}
	else if (!currentFocus) {
		(*currentScene_)->setFocusedDrawable(drawableId);
		if (onFocusChanged_) onFocusChanged_(drawableId);
	}
}

const Identifiable * SceneController::getFocusedDrawable(void) const
{
	return (*currentScene_)->getFocusedDrawable();
}

void SceneController::AddImage(const Image & img)
{
	if (img.isLoaded == true)
	{
		cacheManager.insert(img.path, img.theImg);
		std::cout << img.path << std::endl;

	}
	else
		throw std::invalid_argument("Cant insert an empty image.");
}

const CacheManager<string, ofImage> & SceneController::getCache() const
{
	return cacheManager;
}

SceneNode * SceneController::ensureDrawableExistance(const Identifiable & drawableId)
{
	return (*currentScene_)->ensureDrawableExistance(drawableId);
}