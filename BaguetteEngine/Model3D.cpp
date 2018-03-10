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
	bool isLoaded;

	model_.clear();//May be useless
	isLoaded = model_.loadModel(path);
	setMesh(model_.getMesh(0));
	return isLoaded;
}
