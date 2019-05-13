#include "Light.h"



GLuint Light::cont = 0;
Light::Light()
{
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		enable();
	}
}


Light::~Light()
{
	disable();
}


void Light::disable()
{
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS)
		glDisable(id);
}


void Light::enable()
{
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS)
		glEnable(id);
}


void Light::load(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(glm::value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, glm::value_ptr(posDir));

	glLightfv(id, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, glm::value_ptr(specular));
}


void Light::setPos(glm::fvec3 pos)
{
	posDir = glm::fvec4(pos, 1.0);
}


void Light::setDir(glm::fvec3 dir)
{
	posDir = glm::fvec4(-dir, 0.0);
}


void Light::setAmb(glm::fvec4 amb)
{
	ambient = amb;
}


void Light::setDiff(glm::fvec4 diff)
{
	diffuse = diff;
}


void Light::setSpec(glm::fvec4 spec)
{
	specular = spec;
}