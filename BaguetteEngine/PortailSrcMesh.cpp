#include "PortailSrcMesh.hpp"

PortailSrcMesh::PortailSrcMesh(SceneGraph & scene)
	: scene_(scene)
{
	// type_ = ADrawable::DrawableType::CAMERA;

	plane_.set(1, 1);
	setMesh(plane_.getMeshPtr());
	r_ = false;
}

PortailSrcMesh::~PortailSrcMesh(void)
{
}

void PortailSrcMesh::setDest(AMesh *dest)
{
	dest_ = dest;
	if (dest != nullptr) {
		cam_.setPosition(dest->getPosition());
		// cam_.setOrientation(ofVec3f(-45, 0, 0));
		// set cam rotation perpendiculaire to plane_
	}
}

void PortailSrcMesh::draw_(void)
{
	if (r_) return;

	r_ = true;
	fbo_.destroy();
	fbo_.allocate(520, 520, GL_RGBA);

	std::cout << "dest position: " << dest_->getPosition() << std::endl;
	cam_.setPosition(dest_->getPosition());
	cam_.begin();
		fbo_.begin();
			scene_.render(renderer_);
		fbo_.end();
	cam_.end();
	r_ = false;

	const ofTexture & tex = fbo_.getTextureReference();

	ofImage t;
	

	tex.bind();
		//shader_.begin();
		//	shader_.setUniform1i("texturePresent", true);
		//	shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
				plane_.draw();
		//shader_.end();
	//tex.unbind();
	plane_.draw();
}