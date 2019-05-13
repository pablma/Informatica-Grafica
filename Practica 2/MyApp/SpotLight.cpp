#include "SpotLight.h"



SpotLight::SpotLight() : Light()
{
	//alpha_ = 3.0;
}


SpotLight::~SpotLight()
{
	Light::disable();
}


void SpotLight::load(glm::dmat4 const& modelViewMat)
{
	Light::load(modelViewMat);

	glLightf(id, GL_SPOT_CUTOFF, alpha_);
	glLightf(id, GL_SPOT_EXPONENT, 4.0);
	glLightfv(id, GL_SPOT_DIRECTION, dir_);
}


void SpotLight::setLightDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ)
{
	dir_[0] = dirX;
	dir_[1] = dirY;
	dir_[2] = dirZ;
}


void SpotLight::setAlpha(GLfloat alpha)
{
	alpha_ = alpha;
}