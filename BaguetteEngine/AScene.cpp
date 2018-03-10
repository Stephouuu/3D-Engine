#include "AScene.hpp"

AScene::AScene(void)
	: focusedDrawable_(nullptr)
{
	setSceneColor(ofColor(63, 63, 63));
}

AScene::~AScene(void)
{
}

void AScene::update(float dt)
{
	graph_.update(dt);
}

void AScene::render(ARenderer & renderer)
{
	graph_.render(renderer);
}

void AScene::removeDrawable(const Identifiable & drawableId)
{
	ensureDrawableExistance(drawableId);
	historic_.deleteTransformations(drawableId);
	graph_.detach(drawableId);
}

void AScene::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setPosition(pos);
	historic_.pushTransformation(std::make_pair(drawableId, node->getDrawable()->getLocalTransformMatrix()));
}

void AScene::setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation)
{
	SceneNode *node = ensureDrawableExistance(drawableId);
	ofQuaternion	qOrientation(orientation.x, ofVec3f(1, 0, 0), orientation.y, ofVec3f(0, 1, 0), orientation.z, ofVec3f(0, 0, 1));

	node->getDrawable()->setOrientation(qOrientation);
	historic_.pushTransformation(std::make_pair(drawableId, node->getDrawable()->getLocalTransformMatrix()));
}

void AScene::setDrawableRotation(const Identifiable & drawableId, float degrees)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setRotation(degrees);
}

void AScene::setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setScale(scale);
	historic_.pushTransformation(std::make_pair(drawableId, node->getDrawable()->getLocalTransformMatrix()));
}

void AScene::setDrawableColor(const Identifiable & drawableId, const ofFloatColor & color)
{
	ensureDrawableExistance(drawableId)->getDrawable()->setFillColor(color);
}

void AScene::setDrawableOutlineColor(const Identifiable & drawableId, const ofColor & color)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	if (node) {
		node->getDrawable()->setOutlineColor(color);
	}
}

void AScene::setDrawableOutlineThickness(const Identifiable & drawableId, int thickness)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	if (node) {
		node->getDrawable()->setOutlineThickness(thickness);
	}
}

void AScene::setSceneColor(const ofColor & color)
{
	sceneColor_ = color;
}

const ofColor & AScene::getSceneColor(void) const
{
	return sceneColor_;
}

void AScene::graphContent(SceneNode::TreeData & data) const
{
	graph_.dump(data);
}

void AScene::undo(void)
{
	try {
		const TransformableHistory::Item & t = historic_.undo();
		SceneNode * node = graph_.findNode(t.first);
		if (node) {
			node->getDrawable()->setTransformMatrix(t.second);
		}
	}
	catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
	}
}

void AScene::redo(void)
{
	try {
		const TransformableHistory::Item & t = historic_.redo();
		SceneNode * node = graph_.findNode(t.first);
		if (node) {
			node->getDrawable()->setTransformMatrix(t.second);
		}
	}
	catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
	}
}

void AScene::setFocusedDrawable(const Identifiable & drawableId)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	if (focusedDrawable_) {
		SceneNode *focused = ensureDrawableExistance(*focusedDrawable_);
		if (focused && focused != 0 && focused->getDrawable()) focused->getDrawable()->setFocused(false);
	}
	if (node) {
		if (node->getDrawable()) node->getDrawable()->setFocused(true);
		focusedDrawable_ = node;
	}
}

const Identifiable * AScene::getFocusedDrawable(void) const
{
	return focusedDrawable_;
}

SceneNode * AScene::ensureDrawableExistance(const Identifiable & id)
{
	SceneNode *node = graph_.findNode(id);

	if (!node) {
		std::ostringstream oss;
		oss << "Drawable #" << id << " not found" << std::endl;
		throw std::runtime_error(oss.str());
	}
	return node;
}