#include "EditMenu.hpp"
#include "ACubicCurveVector.hpp"

EditMenu::EditMenu(SceneController & scene)
	: scene_(scene), currentDimension_(3), resetting_(false), isImported(false), yolo_(0)
{
	scene_.setOnTransformationChanged(std::bind(&EditMenu::onTransformationChange, this));

	filterLabel_["Aucun"] = Texture::FilterType::NONE_FILTER;
	filterLabel_["Flou gaussien"] = Texture::FilterType::BLUR;
	filterLabel_["Detection de bordure"] = Texture::FilterType::EDGE_DETECT;
	filterLabel_["Relief"] = Texture::FilterType::EMBROSS;
	filterLabel_["Degrossir"] = Texture::FilterType::SHARPEN;
	filterLabel_["Bordure renforce"] = Texture::FilterType::EDGE_ENFORCED;
	filterLabel_["Masque de flou"] = Texture::FilterType::UNSHARP_MASKING;

	compositionLabel_["Aucun"] = Texture::CompositionType::NONE;
	compositionLabel_["Somme"] = Texture::CompositionType::ADD;
	compositionLabel_["Moyenne"] = Texture::CompositionType::AVG;
	compositionLabel_["Soustraction"] = Texture::CompositionType::SUB;
	compositionLabel_["Multiplication"] = Texture::CompositionType::MUL;
	compositionLabel_["Ecart"] = Texture::CompositionType::DIFF;
	compositionLabel_["Le plus sombre"] = Texture::CompositionType::DARK;
	compositionLabel_["Le plus clair"] = Texture::CompositionType::LIGHT;

	compositionMode_ = Texture::CompositionType::NONE;
}

EditMenu::~EditMenu(void)
{
}

void EditMenu::draw(void)
{
	gui_.draw();

	if (isImported) {
		displayListImage();
		displayListSecondary();
		isImported = false;
	}
}

void EditMenu::setup()
{
	removeListeners();

	colorFill_.setup("Couleur", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));

	position_.setup("Positions", ofVec3f(0, 0, 0), ofVec3f(-30, -30, -30), ofVec3f(30, 30, 30));
	size_.setup("Taille", ofVec3f(1, 1, 1), ofVec3f(0, 0, 0), ofVec3f(30, 30, 30));
	rotation_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360));

	position2d_.setup("Positions", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(1900, 1000));
	size2d_.setup("Taille", ofVec2f(100, 100), ofVec2f(0, 0), ofVec2f(1900, 1000));
	rotation2d_.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(0, 0, 360));
	bezierParams1_.setup("Bezier param 1", ofVec3f(128, 614.4), ofVec3f(128, 614.4), ofVec3f(1900, 1000));
	bezierParams2_.setup("Bezier param 2", ofVec3f(128, 614.4), ofVec3f(128, 614.4), ofVec3f(1900, 1000));
	bezierParams3_.setup("Bezier param 3", ofVec3f(768, 153.6), ofVec3f(768, 153.6), ofVec3f(1900, 1000));
	bezierParams4_.setup("Bezier param 4", ofVec3f(768, 153.6), ofVec3f(768, 153.6), ofVec3f(1900, 1000));

	thickness_.setup("Epaisseur bordure", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(30, 0));
	colorOut_.setup("Couleur bordure", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
	colorScene_.setup("Couleur scene", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));

	perlinNoiseSize_.setup("Parametre bruit de perlin", ofVec3f(300, 300, 0.01f), ofVec3f(100, 100, 0.01f), ofVec3f(1000, 1000, 1));

	selectPrimaryTextures_.setup();
	composition_.setup();
	filter_.setup();
	mode_.setup();
	selectSecondaryTextures_.setup();

	displayListImage();
	displayListSecondary();
	animationButton_.setup("Animations");

	baseSetup();
	refresh(3);
}

void EditMenu::refresh(int newEditorDimension)
{
	currentDimension_ = newEditorDimension;
	gui_.clear();
	gui_.setName("Menu d'edition");
	ofSetBackgroundColor(scene_.getSceneColor());
	if (newEditorDimension == 2) {
		gui_.add(&position2d_);
		gui_.add(&size2d_);
		gui_.add(&rotation2d_);
		gui_.add(&thickness_);
		gui_.add(&colorOut_);
		gui_.add(&colorScene_);
	}
	else {
		gui_.add(&animationButton_);
		gui_.add(&position_);
		gui_.add(&size_);
		gui_.add(&rotation_);
	}
	gui_.add(&colorFill_);
	if (newEditorDimension == 3) {
		gui_.add(&selectPrimaryTextures_);
		gui_.add(&composition_);
		composition_.minimizeAll();
		composition_.minimize();
		gui_.add(&filter_);
	}
}

void EditMenu::update(float dt)
{
	if (yolo_ > 0.000000f) {
		yolo_ -= dt;
		if (yolo_ <= 0.000000f) {
			yolo_ = 0;
			const Identifiable * id = scene_.getFocusedDrawable();
			if (id && (*id) != 0) {
				SceneNode * node = scene_.ensureDrawableExistance(*id);
				if (node->getDrawable()->getTexture(0) == nullptr) {
					node->getDrawable()->setTexture(new Texture, 0);
				}
				node->getDrawable()->getTexture(0)->loadImage(TextureGenerator::perlinNoise(yoloArg_.x, yoloArg_.y, yoloArg_.z));
				for (const auto &e : primaryTextureList_) {
					if (e->getName() == "Bruit de perlin") {
					toggle * t = reinterpret_cast<toggle *>(e);
					if (t->getValue() == false) {
						t->setValue(true);
						}
					}
				}
			}
		}
	}
}

void EditMenu::displayListImage()
{
	toggle *aButton;
	int i = 0;

	primaryTextureList_.clear();
	selectPrimaryTextures_.clear();

	selectPrimaryTextures_.setName("Texture principale");
	aButton = new toggle();

	primaryTextureList_.push_back(aButton->setup("Aucune", false, 20, 20));
	selectPrimaryTextures_.add(primaryTextureList_[i]);
	primaryTextureList_[i++]->addListener(this, &EditMenu::toggleSelectedPrimary);	

	aButton = new toggle();
	primaryTextureList_.push_back(aButton->setup("Bruit de perlin", false, 20, 20));
	selectPrimaryTextures_.add(primaryTextureList_[i]);
	primaryTextureList_[i++]->addListener(this, &EditMenu::toggleSelectedPrimary);

	selectPrimaryTextures_.add(&perlinNoiseSize_);

	for (auto image = scene_.getCache().getObject().begin(); image != scene_.getCache().getObject().end(); ++image)
	{
		string name = image->first;
		aButton = new toggle();
		primaryTextureList_.push_back(aButton->setup(name, false, 20, 20));
		selectPrimaryTextures_.add(primaryTextureList_[i]);
		primaryTextureList_[i++]->addListener(this, &EditMenu::toggleSelectedPrimary);
	}
}

void EditMenu::displayListSecondary()
{
	toggle *aButton;
	int i = 0;

	secondaryTextureList_.clear();
	selectSecondaryTextures_.clear();

	selectSecondaryTextures_.setName("Texture de composition");

	for (auto image = scene_.getCache().getObject().begin(); image != scene_.getCache().getObject().end(); ++image)
	{
		string name = image->first;
		aButton = new toggle();
		secondaryTextureList_.push_back(aButton->setup(name, false, 20, 20));
		selectSecondaryTextures_.add(secondaryTextureList_[i]);
		secondaryTextureList_[i++]->addListener(this, &EditMenu::toggleSelectedSecondary);
	}
}

void EditMenu::focus(const Identifiable & id)
{
	SceneNode * node = scene_.ensureDrawableExistance(id);

	if (node) {
		updateValues(node);
		setupGuiFromDrawableType(node->getDrawable());
	}
}

void EditMenu::windowsResized(const ofPoint & size)
{
	const Identifiable * id = scene_.getFocusedDrawable();

	gui_.clear();
	gui_.setName("Menu d'edition");
	// setup();

	refresh(currentDimension_);
	displayListImage();
	displayListSecondary();
	if (id) {
		focus(*id);
	}
	gui_.setPosition(size.x - gui_.getWidth(), 10);
}

void EditMenu::vecSliderPositionChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, vec.z), !resetting_);
}

void EditMenu::vec3SliderPerlinChange(ofVec3f & vec)
{
	yolo_ = 0.400f;
	yoloArg_ = vec;
}

void EditMenu::vecSliderSizeChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, vec.z), !resetting_);
}

void EditMenu::vecSliderColorChange(ofColor & color)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableColor(*focused, color);
}

void EditMenu::vecSliderRotationChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableRotation(*focused, vec, !resetting_);
}

void EditMenu::vec2SliderPositionChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawablePosition(*focused, ofVec3f(vec.x, vec.y, 0), !resetting_);
}

void EditMenu::vec2SliderSizeChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableScale(*focused, ofVec3f(vec.x, vec.y, 0), !resetting_);
}

void EditMenu::vec2SliderRotationChange(ofVec3f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableRotation(*focused, vec.z, !resetting_);
}

void EditMenu::vec2SliderBezierChange(ofVec2f & p)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr && (*focused) != 0) {
		SceneNode *node = scene_.ensureDrawableExistance(*focused);
		if (node) {
			ACubicCurveVector *b = dynamic_cast<ACubicCurveVector *>(node->getDrawable());
			if (b) {
				b->setParam({
					bezierParams1_.getValue(),
					bezierParams2_.getValue(),
					bezierParams3_.getValue(),
					bezierParams4_.getValue(),
				});
			}
		}
	}
}

void EditMenu::buttonPressedAnimations(const void * sender)
{
	ofxButton				*button = (ofxButton*)sender;
	const Identifiable		*focused = scene_.getFocusedDrawable();
	AMesh					*mesh;

	if (button->getName() == "Animations")
	{
		if (focused != nullptr)
		{
			mesh = dynamic_cast<AMesh*>(scene_.ensureDrawableExistance(*focused)->getDrawable());
			if (mesh->getType() == AMesh::InstantiableMesh::MODEL)
			{
				Model3D	*model = dynamic_cast<Model3D*>(mesh);

				if (model->isPlayingAnimations())
					model->stopAnimations();
				else
					model->playAnimations();
			}
		}
		//Need to stop animation
	}

}

void EditMenu::onColorOutChange(ofColor & color)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableOutlineColor(*focused, color);
}

void EditMenu::onThicknessChange(ofVec2f & vec)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused != nullptr) scene_.setDrawableOutlineThickness(*focused, vec.x);
}

void EditMenu::onColorSceneChange(ofColor & color)
{
	scene_.setSceneColor(color);
	ofSetBackgroundColor(color);
}

void EditMenu::toggleSelectedFilter(const void * sender, bool & value)
{
	ofParameter<bool> * p = (ofParameter<bool> *) sender;

	if (!resetting_) {
		resetting_ = true;
		for (const auto & e : filterList_) {
			if (e->getName() != p->getName()) {
				reinterpret_cast<toggle *>(e)->setValue(false);
			}
		}
		const Identifiable * id = scene_.getFocusedDrawable();
		if (id && (*id) != 0) {
			SceneNode * node = scene_.ensureDrawableExistance(*id);
			if (node->getDrawable()->getTexture(0) == nullptr) {
				node->getDrawable()->setTexture(new Texture, 0);
			}
			node->getDrawable()->getTexture(0)->setFilter(filterLabel_[p->getName()]);
		}
		value = true;
		resetting_ = false;
	}
}

void EditMenu::toggleSelectedMode(const void * sender, bool & value)
{
	ofParameter<bool> * p = (ofParameter<bool> *) sender;

	if (!resetting_) {
		resetting_ = true;
		composition_.clear();
		composition_.setName("Composition");
		for (const auto & e : modeCompositionList_) {
			if (e->getName() != p->getName()) {
				reinterpret_cast<toggle *>(e)->setValue(false);
			}
		}
		value = true;
		if (p->getName() == "Aucun") {
			composition_.add(&mode_);
		} else {
			composition_.add(&mode_);
			composition_.add(&selectSecondaryTextures_);
		}

		compositionMode_ = compositionLabel_[p->getName()];

		resetting_ = false;
	}
}

void EditMenu::toggleSelectedPrimary(const void * sender, bool & value)
{
	ofParameter<bool> * p = (ofParameter<bool> *) sender;

	if (!resetting_) {
		resetting_ = true;
		for (const auto & e : primaryTextureList_) {
			if (e->getName() != p->getName()) {
				reinterpret_cast<toggle *>(e)->setValue(false);
			}
		}
		value = true;

		const Identifiable * id = scene_.getFocusedDrawable();
		if (id && (*id) != 0) {
			SceneNode * node = scene_.ensureDrawableExistance(*id);
			if (node->getDrawable()->getTexture(0) == nullptr) {
				node->getDrawable()->setTexture(new Texture, 0);
			}
			if (p->getName() == "Aucune") {
				node->getDrawable()->setTexture(nullptr, 0);
			} else {
				if (p->getName() != "Bruit de perlin") {
					node->getDrawable()->getTexture(0)->loadImage(&scene_.getCache().at(p->getName()));
				} else {
					node->getDrawable()->getTexture(0)->loadImage(TextureGenerator::perlinNoise(150, 150, 0.01f));
				}
			}
		}

		resetting_ = false;
	}
}

void EditMenu::toggleSelectedSecondary(const void * sender, bool & value)
{
	ofParameter<bool> * p = (ofParameter<bool> *) sender;

	if (!resetting_) {
		resetting_ = true;
		for (const auto & e : secondaryTextureList_) {
			if (e->getName() != p->getName()) {
				reinterpret_cast<toggle *>(e)->setValue(false);
			}
		}
		value = true;

		const Identifiable * id = scene_.getFocusedDrawable();
		if (id && (*id) != 0) {
			SceneNode * node = scene_.ensureDrawableExistance(*id);
			if (node->getDrawable()->getTexture(0) == nullptr) {
				node->getDrawable()->setTexture(new Texture, 0);
			}
			node->getDrawable()->getTexture(0)->addComposition(&scene_.getCache().at(p->getName()), compositionMode_);
		}

		resetting_ = false;
	}
}

void EditMenu::baseSetup()
{
	gui_.setup();
	gui_.setName("Menu d'edition");
	gui_.setPosition(820, 10);

	initFilters();
	initModeComposition();

	composition_.add(&mode_);

	mode_.minimizeAll();

	selectPrimaryTextures_.setName("Texture principale");
	composition_.setName("Composition");
	filter_.setName("Filtres");

	initListeners();

	gui_.add(&position_);
	gui_.add(&size_);
	gui_.add(&colorFill_);
	gui_.add(&rotation_);
}

bool EditMenu::getIsImported()
{
	return isImported;
}

void EditMenu::setIsImported(bool value)
{
	isImported = value;
}

void EditMenu::updateValues(SceneNode *node)
{
	ADrawable *currentDrawable = node->getDrawable();

	resetting_ = true;
	if (currentDimension_ == 3)
	{
		if (currentDrawable) {
			ofVec3f position = currentDrawable->getPosition();
			position_.setValue(ofVec3f(position.x, position.y, position.z));
			ofVec3f scale = currentDrawable->getScale();
			size_.setValue(ofVec3f(scale.x, scale.y, scale.z));
			ofColor color = currentDrawable->getFillColor();
			colorFill_.setValue(ofColor(color.r, color.g, color.b, color.a));
			ofVec3f rotater = currentDrawable->getOrientationEuler();
			rotation_.setValue(rotater);
		}
		else {
			position_.setValue(ofVec3f(0, 0, 0));
			size_.setValue(ofVec3f(0, 0, 0));
			colorFill_.setValue(ofColor(0, 0, 0, 0));
		}
	}
	else {
		if (currentDrawable) {
			ofVec3f position = currentDrawable->getPosition();
			position2d_.setValue(ofVec2f(position.x, position.y));
			ofVec3f scale = currentDrawable->getScale();
			size2d_.setValue(ofVec2f(scale.x, scale.y));
			float rotation = currentDrawable->getRotation();
			rotation2d_.setValue(ofVec3f(0, 0, rotation));
			ofColor fillColor = currentDrawable->getFillColor();
			colorFill_.setValue(fillColor);
			ofColor outColor = currentDrawable->getOutlineColor();
			colorOut_.setValue(outColor);
			int thickness = currentDrawable->getOutlineThickness();
			thickness_.setValue(ofVec2f(thickness, 0));

			updateGuiFromDrawableType(currentDrawable);
		}
		else {
			position2d_.setValue(ofVec2f(0, 0));
			size2d_.setValue(ofVec2f(0, 0));
		}
	}

	ofColor sceneColor = scene_.getSceneColor();
	colorScene_.setValue(sceneColor);
	resetting_ = false;
}

void EditMenu::onTransformationChange(void)
{
	const Identifiable * focused = scene_.getFocusedDrawable();
	if (focused && focused->getID() > 0) {
		SceneNode * node = scene_.ensureDrawableExistance(*focused);
		updateValues(node);
	}
}

void EditMenu::initFilters(void)
{
	toggle *tgl;
	int i = 0;

	filterList_.clear();
	filter_.clear();

	for (const auto &e : filterLabel_)
	{
		tgl = new toggle();

		filterList_.push_back(tgl->setup(e.first, false, 20, 20));
		if (i == 0) {
			tgl->setValue(true);
		}
		
		filter_.add(filterList_[i]);
		filterList_[i++]->addListener(this, &EditMenu::toggleSelectedFilter);
	}
}

void EditMenu::initListeners(void)
{
	colorFill_.getParameter().cast<ofColor>().addListener(this, &EditMenu::vecSliderColorChange);

	position_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderSizeChange);
	rotation_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vecSliderRotationChange);

	position2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderPositionChange);
	size2d_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderSizeChange);
	rotation2d_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vec2SliderRotationChange);
	bezierParams1_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams2_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams3_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams4_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::vec2SliderBezierChange);

	thickness_.getParameter().cast<ofVec2f>().addListener(this, &EditMenu::onThicknessChange);
	colorOut_.getParameter().cast<ofColor>().addListener(this, &EditMenu::onColorOutChange);
	colorScene_.getParameter().cast<ofColor>().addListener(this, &EditMenu::onColorSceneChange);

	perlinNoiseSize_.getParameter().cast<ofVec3f>().addListener(this, &EditMenu::vec3SliderPerlinChange);
}

void EditMenu::initModeComposition(void)
{
	toggle *tgl;
	int i = 0;

	modeCompositionList_.clear();
	mode_.clear();

	mode_.setName("Mode de composition");
	for (const auto &e : compositionLabel_)
	{
		tgl = new toggle();

		modeCompositionList_.push_back(tgl->setup(e.first, false, 20, 20));
		if (i == 0) {
			tgl->setValue(true);
		}

		mode_.add(modeCompositionList_[i]);
		modeCompositionList_[i++]->addListener(this, &EditMenu::toggleSelectedMode);
	}

	animationButton_.addListener(this, &EditMenu::buttonPressedAnimations);
}

void EditMenu::removeListeners(void)
{
	colorFill_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::vecSliderColorChange);

	position_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderPositionChange);
	size_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderSizeChange);
	rotation_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vecSliderRotationChange);

	position2d_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderPositionChange);
	size2d_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderSizeChange);
	rotation2d_.getParameter().cast<ofVec3f>().removeListener(this, &EditMenu::vec2SliderRotationChange);
	bezierParams1_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams2_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams3_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderBezierChange);
	bezierParams4_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::vec2SliderBezierChange);

	thickness_.getParameter().cast<ofVec2f>().removeListener(this, &EditMenu::onThicknessChange);
	colorOut_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::onColorOutChange);
	colorScene_.getParameter().cast<ofColor>().removeListener(this, &EditMenu::onColorSceneChange);

	for (const auto &e : primaryTextureList_)
		e->removeListener(this, &EditMenu::toggleSelectedPrimary);
	for (const auto &e : secondaryTextureList_)
		e->removeListener(this, &EditMenu::toggleSelectedSecondary);
	for (const auto &e : filterList_)
		e->removeListener(this, &EditMenu::toggleSelectedFilter);
	for (const auto &e : modeCompositionList_)
		e->removeListener(this, &EditMenu::toggleSelectedMode);
	animationButton_.removeListener(this, &EditMenu::buttonPressedAnimations);
}

void EditMenu::setupGuiFromDrawableType(const ADrawable * drawable)
{
	if (!drawable)
		return;

	refresh(currentDimension_);
	if (dynamic_cast<const ACubicCurveVector *>(drawable)) {
		gui_.add(&bezierParams1_);
		gui_.add(&bezierParams2_);
		gui_.add(&bezierParams3_);
		gui_.add(&bezierParams4_);
	}
}

void EditMenu::updateGuiFromDrawableType(const ADrawable * drawable)
{
	if (!drawable)
		return;

	if (dynamic_cast<const BezierCubicVector *>(drawable)) {
		// todo ...
	}
}