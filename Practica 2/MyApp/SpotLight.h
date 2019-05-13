#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight();
	~SpotLight();
	virtual void load(glm::dmat4 const& modelViewMat);
	void setLightDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ);
	void setAlpha(GLfloat alpha);
private:
	GLfloat dir_[3];
	GLdouble alpha_;
};