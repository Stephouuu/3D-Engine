#pragma once

#include "AMesh.hpp"
#include "EasyCamera.hpp"

class PortailDstMesh : public AMesh
{
public:
	PortailDstMesh(void);
	virtual ~PortailDstMesh(void);

	void setSource(AMesh *src);

private:
	virtual void draw_(void);

private:
	AMesh * src_;
	ofPlanePrimitive plane_;
	EasyCamera cam_;
	ofFbo fbo_;
};

