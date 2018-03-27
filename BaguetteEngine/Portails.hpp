#pragma once

#include <vector>

#include "ARenderer.hpp"
#include "SceneGraph.hpp"
#include "Identifiable.hpp"

#include "Portail.hpp"

class Portails
{
public:
	Portails(void);
	~Portails(void);

	void refresh(ARenderer & renderer, SceneGraph & scene);

	void addPortail(const Identifiable & p1, const Identifiable & p2);

private:
	std::vector<Portail *> portails_;
};

