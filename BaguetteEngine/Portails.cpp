#include "Portails.hpp"

Portails::Portails(void)
{
}

Portails::~Portails(void)
{
	for (auto & it : portails_) {
		delete it;
	}
}

void Portails::refresh(ARenderer & renderer, SceneGraph & scene)
{
	std::vector<Portail *>::iterator it = std::begin(portails_);
	
	while (it != std::end(portails_)) {
		if (!(*it)->refresh(renderer, scene)) {
			delete (*it);
			it = portails_.erase(it);
		}
		else {
			++it;
		}
	}
}

void Portails::addPortail(const SceneNode::Ptr & n1, const SceneNode::Ptr & n2)
{
	n1->getDrawable()->setShader("shaders/portal.vert", "shaders/portal_orange.frag");
	n1->getDrawable()->setTexture(new Texture("portal.png"), 0);
	n1->getDrawable()->setTexture(new Texture("mur.jpg"), 1);

	n2->getDrawable()->setShader("shaders/portal.vert", "shaders/portal_blue.frag");
	n2->getDrawable()->setTexture(new Texture("portal.png"), 0);
	n2->getDrawable()->setTexture(new Texture("mur.jpg"), 1);

	portails_.push_back(new Portail(*n1, *n2));
}