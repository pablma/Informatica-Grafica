#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


class Material
{
public:
	Material();
	~Material();
	virtual void load();
	void setBronze();
	void setChrome();
	void setSilver();
	void setCopper();
private:
	glm::fvec4 ambient, diffuse, specular; // coeficientes de reflexi�n
	GLfloat expF; // exponente especular
	GLuint face = GL_FRONT_AND_BACK; // ambos lados
	GLuint sh = GL_SMOOTH; // smooth shading
};

