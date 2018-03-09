#include "AScene.hpp"

AScene::AScene(void)
	: focusedDrawable_(nullptr)
{
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

	std::cout << "Set drawable rotation" << std::endl;
	node->getDrawable()->setOrientation(orientation);
	historic_.pushTransformation(std::make_pair(drawableId, node->getDrawable()->getLocalTransformMatrix()));
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

	if (node) {
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