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

	void refresh(ARenderer & renderer, SceneGraph & scene, LightShader & lightShader);

	void addPortail(const SceneNode::Ptr & n1, const SceneNode::Ptr & n2);

private:
	std::vector<Portail *> portails_;
};

