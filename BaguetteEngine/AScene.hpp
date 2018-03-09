#pragma once

#include "ARenderer.hpp"
#include "Identifiable.hpp"

class AScene
{
public:
	AScene(void);
	virtual ~AScene(void);

	/* void update(float dt);
	void render(ARenderer & renderer);

	int selected(int x, int y);

	const Identifiable & instanciateMesh(AMesh::InstantiableMesh meshType, const Identifiable & parent = Identifiable());
	void removeMesh(const Identifiable & meshId);

	void setMeshPosition(const Identifiable & meshId, const ofVec3f & pos);
	void setMeshRotation(const Identifiable & meshId, float degrees, const ofVec3f & axis);
	void setMeshScale(const Identifiable & meshId, const ofVec3f & scale);
	void setMeshColor(const Identifiable & meshId, const ofFloatColor & color);

	void graphContent(SceneNode::TreeData & data) const;

	void undo(void);
	void redo(void);

	void setFocusedMesh(const Identifiable & id);
	const Identifiable * getFocusedMesh(void) const;

	void AddImage(const Image & img);

	SceneNode * ensureMeshExistance(const Identifiable & id); */
};

