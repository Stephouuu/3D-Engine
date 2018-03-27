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

void Portails::addPortail(const Identifiable & p1, const Identifiable & p2)
{
	portails_.push_back(new Portail(p1, p2));
}