#include "AScene.hpp"

AScene::AScene(void)
	: dtUpdate_(0.000000f), focusedDrawable_(nullptr)
{
	setSceneColor(ofColor(63, 63, 63));
}

AScene::~AScene(void)
{
}

void AScene::update(float dt)
{
	if (dtUpdate_ > 0.000000f) {
		dtUpdate_ -= dt;
		if (dtUpdate_ <= 0.00000f) {
			dtUpdate_ = 0;
			const Identifiable * focused = getFocusedDrawable();
			if (focused && focused->getID() > 0) {
				SceneNode *node = ensureDrawableExistance(*focused);
				historic_.pushTransformation(std::make_pair(*focused, node->getDrawable()->getLocalTransformMatrix()));
			}
		}
	}
	graph_.update(dt);
}

void AScene::render(ARenderer & renderer)
{
	graph_.render(renderer);
}

void AScene::removeDrawable(const Identifiable & drawableId)
{
	std::vector<Light::Ptr>::iterator it;

	ensureDrawableExistance(drawableId);
	historic_.deleteTransformations(drawableId);
	graph_.detach(drawableId);
	for (it = lights_.begin(); it != lights_.end(); ++it)
	{
		if ((*it)->getDrawableId() == drawableId)
		{
			lights_.erase(it);
			break;
		}
	}
}

void AScene::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setPosition(pos);
	if (save) dtUpdate_ = 0.400f;
}

void AScene::setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation, bool save)
{
	SceneNode *node = ensureDrawableExistance(drawableId);
	ofQuaternion	qOrientation(orientation.x, ofVec3f(1, 0, 0), orientation.y, ofVec3f(0, 1, 0), orientation.z, ofVec3f(0, 0, 1));

	node->getDrawable()->setOrientation(qOrientation);
	if (save) dtUpdate_ = 0.400f;
}

void AScene::setDrawableRotation(const Identifiable & drawableId, float degrees, bool save)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setRotation(degrees);
	(void)save;
}

void AScene::setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale, bool save)
{
	SceneNode *node = ensureDrawableExistance(drawableId);

	node->getDrawable()->setScale(scale);
	if (save) dtUpdate_ = 0.400f;
}

void AScene::setDrawableColor(const Identifiable & drawableId, const ofFloatColor & color)
{
	ensureDrawableExistance(drawableId)->getDrawable()->setFillColor(color);
}

void AScene::setDrawableDiffuseColor(const Identifiable & drawableId, const ofFloatColor & color)
{
	ensureDrawableExistance(drawableId)->getDrawable()->setDiffuseColor(color);
}

void AScene::setDrawableSpecularColor(const Identifiable & drawableId, const ofFloatColor & color)
{
	ensureDrawableExistance(drawableId)->getDrawable()->setSpecularColor(color);
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
		return nullptr;
	}
	return node;
}

void AScene::setLightModel(Light::LightModel model)
{
	std::vector<Light::Ptr>::iterator	it;

	for (it = lights_.begin(); it != lights_.end(); ++it)
		(*it)->setLightModel(model);
}