//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Camera.h"
#include "Entities.h"
#include "SpotLight.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:

	  Scene(Camera* cam): camera(cam) { };
	  ~Scene();
      void init();
	  void render();    
	  Diabolo* getDiabolo();
	  Photo* getPhoto();
	  Light* getDirectionalLight_();
	  void update(GLuint timeElapsed);
	  std::vector<Light*> getLights();

protected:
	  
	  Camera* camera = nullptr;
	  std::vector<Entity*> objetos;
	  std::vector<Light*> lights_;
	  
	  // Viewport
	  GLint VpWidth;
	  GLint VpHeight;

	  // Objects
	  Diabolo* diabolo_ = nullptr;
	  Photo* photo_ = nullptr;
	  Sphere* moonSphere_ = nullptr;
	  Sphere* sunSphere_ = nullptr;
	  Sphere* marsSphere_ = nullptr;
	  Terrain* terrain_ = nullptr;

	  // Lights
	  Light* directionalLight_ = nullptr;
	  SpotLight* cameraLight_ = nullptr;

	  // Textures
	  Texture moonText_;
	  Texture SunText_;
	  Texture MarsText_;
	  Texture VenusText_;
	  Texture TerrainText_;

	  // Materials
	  Material bronzeMat_;
	  Material ChromeMat_;
	  Material SilverMat_;
	  Material CopperMat_;

	  // Matrix
	  glm::dmat4 moonMatrix_;
	  glm::dmat4 sunMatrix_;
	  glm::dmat4 marsMatrix_;
	  glm::dmat4 venusMatrix_;

};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

