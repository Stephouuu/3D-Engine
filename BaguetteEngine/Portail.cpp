#include "Portail.hpp"

Portail::Portail(const Identifiable & p1, const Identifiable & p2)
	: p1_(p1), p2_(p2)
{
	fbo1_.allocate(1024, 1024, GL_RGB);
	fbo2_.allocate(1024, 1024, GL_RGB);
}

Portail::~Portail(void)
{
	std::clog << "delete portail between #" << p1_ << " and #" << p2_ << std::endl;
	if (fbo1_.isAllocated()) fbo1_.clear();
	if (fbo2_.isAllocated()) fbo2_.clear();
}

bool Portail::refresh(ARenderer & renderer, SceneGraph & scene)
{
	SceneNode *p1Node = scene.findNode(p1_);
	SceneNode *p2Node = scene.findNode(p2_);

	if (p1Node && p2Node) {
		pcam1_.setPosition(p1Node->getDrawable()->getPosition());
		pcam1_.setOrientation(p1Node->getDrawable()->getOrientationQuat());
		pcam2_.setPosition(p2Node->getDrawable()->getPosition());
		pcam2_.setOrientation(p2Node->getDrawable()->getOrientationQuat());

		fbo1_.begin();
			ofClear(ofGetBackgroundColor());
			pcam2_.begin();
				scene.render(renderer);
			pcam2_.end();
		fbo1_.end();

		fbo2_.begin();
			ofClear(ofGetBackgroundColor());
			pcam1_.begin();
				scene.render(renderer);
			pcam1_.end();
		fbo2_.end();

		p1Node->getDrawable()->setTexture(new Texture(fbo1_), 2);
		p2Node->getDrawable()->setTexture(new Texture(fbo2_), 2);
		return true;
	}
	return false;
}