#include "Model3DGenerator.hpp"

Model3DGenerator::Model3DGenerator()
{
	model_ = new Model3D;
}

Model3DGenerator::Model3DGenerator(const std::string & path)
{
	model_ = new Model3D;
	model_->load(path);
}


Model3DGenerator::~Model3DGenerator()
{
}

AMesh * Model3DGenerator::operator()(void) const
{
	return generate();
}

AMesh * Model3DGenerator::generate() const
{
	return model_;
}

void Model3DGenerator::setPosition(const ofVec3f pos)
{
	model_->setPosition(pos);
}

bool Model3DGenerator::loadModel(const string & path)
{
	return (model_->load(path));
}
