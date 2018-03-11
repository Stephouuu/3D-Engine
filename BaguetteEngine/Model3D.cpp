#include "Model3D.hpp"

Model3D::Model3D()
{
	setMesh(ofMesh());
	meshType_ = AMesh::MODEL;
}

Model3D::~Model3D()
{
}

bool Model3D::load(const string & path)
{
	bool		isLoaded;

	model_.clear();
	isLoaded = model_.loadModel(path);
	modelMesh_ = model_.getMesh(0);
	setMesh(&modelMesh_);
	return isLoaded;
}
