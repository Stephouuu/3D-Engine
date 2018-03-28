#include "Portail.hpp"

Portail::Portail(const Identifiable & p1, const Identifiable & p2)
	: p1_(p1), p2_(p2)
{
	fbo1_.allocate(1024, 1024, GL_RGB);
	fbo2_.allocate(1024, 1024, GL_RGB);
}

Portail::~Portail(void)
{
	if (fbo1_.isAllocated()) fbo1_.clear();
	if (fbo2_.isAllocated()) fbo2_.clear();
}

bool Portail::refresh(ARenderer & renderer, SceneGraph & scene)
{
	SceneNode *p1Node = scene.findNode(p1_);
	SceneNode *p2Node = scene.findNode(p2_);
	ofColor c = ofGetBackgroundColor();

	if (!p1Node || !p2Node)
		return false;
	updateCamerasTransformation(p1Node, p2Node);
	fbo1_.begin();
		ofClear({ (float)c.r, (float)c.g, (float)c.b, 255 });
		pcam2_.begin();
			scene.render(renderer, pcam2_);
		pcam2_.end();
	fbo1_.end();
	fbo2_.begin();
		ofClear({ (float)c.r, (float)c.g, (float)c.b, 0 });
		pcam1_.begin();
			scene.render(renderer, pcam1_);
		pcam1_.end();
	fbo2_.end();
	updatePortalTextures(p1Node, p2Node);
	return true;
}

void Portail::updateCamerasTransformation(SceneNode *n1, SceneNode *n2)
{
	pcam1_.setPosition(n1->getDrawable()->getPosition());
	pcam1_.setOrientation(n1->getDrawable()->getOrientationQuat());

	pcam2_.setPosition(n2->getDrawable()->getPosition());
	pcam2_.setOrientation(n2->getDrawable()->getOrientationQuat());
}

void Portail::updatePortalTextures(SceneNode *n1, SceneNode *n2)
{
	n1->getDrawable()->setTexture(new Texture(fbo1_), 1);
	n2->getDrawable()->setTexture(new Texture(fbo2_), 1);
}