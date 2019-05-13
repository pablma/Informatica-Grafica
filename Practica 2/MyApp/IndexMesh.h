#pragma once
#include "Mesh.h"


class IndexMesh : public Mesh
{
public:
	IndexMesh();
	~IndexMesh();
	virtual void draw();
	static IndexMesh* generateTerrain();
protected:
	void enable();
	void disable();
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
	GLuint* indices = nullptr;
	GLuint numIndices = 0;
};

