#include "Model3D.hpp"

Model3D::Model3D()
{
	meshType_ = AMesh::MODEL;
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
	modelMesh_ = model_.getMesh(0);
	std::cout << "Scene max = " << model_.getSceneMax() << std::endl;
	setMesh(&modelMesh_);
	model_.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model_.playAllAnimations();
	animNb = model_.getAnimationCount();
	return isLoaded;
}

void Model3D::update(float dt)
{
	model_.update();

	if (model_.getAnimationCount() > 0)
		modelMesh_ = model_.getCurrentAnimatedMesh(0);
}

void Model3D::draw_(void)
{
	ofEnableDepthTest();
	modelMesh_.draw();
}