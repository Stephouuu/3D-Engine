#include "Model3D.hpp"

Model3D::Model3D()
{
	meshType_ = AMesh::MODEL;
	isPlayingAnimations_ = false;
}

Model3D::~Model3D()
{
}

bool Model3D::load(const string & path)
{
	bool			isLoaded;
	unsigned int	animNb = 0;

	model_.clear();
	isLoaded = model_.loadModel(path);
	if (isLoaded)
	{
		modelMesh_ = model_.getMesh(0);
		if (model_.getAnimationCount() > 0)
		{
			model_.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			model_.playAllAnimations();
			isPlayingAnimations_ = true;
		}
		animNb = model_.getAnimationCount();
	}
	else
	{
		modelMesh_ = ofMesh();
		modelMesh_.addVertex(ofVec3f(0, 0, 0));
	}

	setMesh(&modelMesh_);
	return isLoaded;
}

void Model3D::stopAnimations()
{
	if (model_.getAnimationCount() <= 0)
		return;
	model_.stopAllAnimations();
	isPlayingAnimations_ = false;
}

void Model3D::playAnimations()
{
	if (model_.getAnimationCount() <= 0)
		return;
	model_.playAllAnimations();
	isPlayingAnimations_ = true;
}

bool Model3D::isPlayingAnimations() const
{
	return isPlayingAnimations_;
}

void Model3D::update(float dt)
{
	model_.update();

	if (model_.getAnimationCount() > 0 && isPlayingAnimations_ == true)
		modelMesh_ = model_.getCurrentAnimatedMesh(0);
}

void Model3D::draw_(void)
{
	modelMesh_.draw();
}