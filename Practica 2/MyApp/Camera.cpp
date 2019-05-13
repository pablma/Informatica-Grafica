#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }
 //------------------------------------------------------------------------

 void Viewport::setPosition(GLint posX, GLint posY)
 {
	 x = posX;
	 y = posY;
	 set();
 }
//-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
  eye = dvec3(0, 0, 500);
  look = dvec3(0, 0, 0);
  up = dvec3(0, 1, 0);

  front = -(normalize(eye - look));
  right = normalize(cross(up, -front));
  up_ = cross(-front, right);

  pitch_ = degrees(asin(front.y));
  yaw_ = degrees(asin(front.x / cos(radians(pitch_))));
  roll_ = degrees(asin(up.x));

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye = dvec3(500, 500, 500);
  look = dvec3(0, 10, 0);
  up = dvec3(0, 1, 0);

  front = -(normalize(eye - look));
  right = normalize(cross(up, -front));
  up_ = cross(-front, right);

  pitch_ = degrees(asin(front.y));
  yaw_ = degrees(asin(front.x / cos(radians(pitch_))));
  roll_ = degrees(asin(up.x));

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
  rotatePY(a, 0);
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
  rotatePY(0, a);
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a)
{
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
  rolling(a);
}
//-------------------------------------------------------------------------

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw)
{
	pitch_ += incrPitch;
	yaw_ += incrYaw;

	// Con estas instrucciones limitamos el giro que puede hacer la camara
	if (pitch_ > 89.5) pitch_ = 89.5;
	else if (pitch_ < -89.5) pitch_ = -89.5;

	/*if (yaw_ > 89.5) yaw_ = 89.5;
	else if (yaw_ < -89.5) yaw_ = -89.5;*/

	front.x = sin(radians(yaw_)) * cos(radians(pitch_));
	front.y = sin(radians(pitch_));
	front.z = -cos(radians(yaw_)) * cos(radians(pitch_));
	
	front = glm::normalize(front);
	right = normalize(cross(up, -front));
	up_ = normalize(cross(-front, right));

	look = eye + front;

	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::rolling(GLdouble incRoll)
{
	roll_ += incRoll;

	/*if (roll_ > 89.5) roll_ = 89.5;
	else if (roll_ < -89.5) roll_ = -89.5;*/

	//Modificar up en x e y
	up.x = sin(radians(roll_));
	up.y = cos(radians(roll_));


	right = normalize(cross(up, -front));
	up_ = normalize(cross(-front, right));

	look = eye + front;

	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if(orto)
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	else 
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);


  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	eye += (right * cs);
	look += (right * cs);
	viewMat = lookAt(eye, look, up);
}
//--------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs)
{
	eye += (front * cs);
	look += (front * cs);
	viewMat = lookAt(eye, look, up);
}
//--------------------------------------------------------------------------

void Camera::moveUD(GLdouble cs)
{
	eye += (up_ * cs);
	look += (up_ * cs);
	viewMat = lookAt(eye, look, up);
}
//--------------------------------------------------------------------------

void Camera::setPrj()
{
	glMatrixMode(GL_PROJECTION);
	
	if (orto)
	{
		projMat = frustum(xLeft, xRight, yBot, yTop, nearVal, farVal);
		orto = false;
	}
	else
	{
		projMat = ortho(xLeft, xRight, yBot, yTop, nearVal, farVal);
		orto = true;
	}

	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}


GLdouble Camera::getX()
{
	return eye.x;
}


GLdouble Camera::getY()
{
	return eye.y;
}


GLdouble Camera::getZ()
{
	return eye.z;
}


GLdouble Camera::getDirX()
{
	return front.x;
}


GLdouble Camera::getDirY()
{
	return front.y;
}


GLdouble Camera::getDirZ()
{
	return front.z;
}