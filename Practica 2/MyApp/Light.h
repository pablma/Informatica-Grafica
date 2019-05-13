#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Light
{
public:

	Light();
	~Light();
	void disable();
	void enable();
	virtual void load(glm::dmat4 const& modelViewMat);
	virtual void setPos(glm::fvec3 pos);
	virtual void setDir(glm::fvec3 dir);
	void setAmb(glm::fvec4 amb);
	void setDiff(glm::fvec4 diff);
	void setSpec(glm::fvec4 spec);

protected:

	static GLuint cont; // valor inicial cont = 0, esto debería ser static
	GLuint id = GL_MAX_LIGHTS; // GL_LIGHTi
	// Las componentes difusa y ambiente representan el color del material
	// La componente especular representa los reflejos del material
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };

};

