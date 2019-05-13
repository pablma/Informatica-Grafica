#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  camera->setAZ();
  
  //Establezco el tamaño del ViewPort
  VpWidth = camera->getVP()->getW() / 2;
  VpHeight = camera->getVP()->getH() / 2;

  // lights
  // textures  

  // objects
  
  //objetos.push_back(new EjesRGB(200.0));
  //objetos.push_back(new TriangleRGB(75.0));
  //objetos.push_back(new TriPyramid(150.0, 150.0));
  //objetos.push_back(new ContCubo(150.0));
  //objetos.push_back(new Dragon(3000));
  //objetos.push_back(new Poliespiral(glm::dvec2(0,0), 0, 160.0, 1.0, 1.0, 50));
  //objetos.push_back(new Diabolo(75.0, 75.0, 200, 100));
  //objetos.push_back(new Cubo(100.0));
  //objetos.push_back(new rectangle(150.0, 150.0));
  //objetos.push_back(new rectangleTex(150.0, 150.0, 1, 1));
  //objetos.push_back(new TriPyramidTex(150.0, 150.0));
  //objetos.push_back(new ContCuboTex(150.0));

  // ESCENA PRACTICA 1
  objetos.push_back(new Suelo(500.0, 500.0, 0.0, -150.0));
  objetos.push_back(new Photo(100.0, 100.0, 100.0, -149.0));
  objetos.push_back(new Grass(100.0, 100.0, 150.0, -100.0, -150.0, 1, 1, 45.0));
  objetos.push_back(new Grass(150.0, 100.0, 150.0, -100.0, -150.0, 1, 1, -45.0));
  objetos.push_back(new GlassPot(100.0, 150.0, -100.0, -150.0));

  d = new Diabolo(75.0, 75.0, 200, 100);
  objetos.push_back(d);

  objetos.push_back(new CuboTex(100.0, 0.0, -100.0));

  
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
  glMatrixMode(GL_MODELVIEW);
  
  //Lo comentado es para hacer que se divida en 4 bloques la pantalla
  
  /*camera->getVP()->setSize(VpWidth, VpHeight);
  
  GLint VpX, VpY;
  VpX = VpY = 0;

  auto it = objetos.begin();

  for (int i = 0; i < 2; i++)
  {
	  for (int j = 0; j < 2; j++)
	  {
		  camera->getVP()->setPosition(VpX, VpY);
		  (*it)->render(camera->getViewMat());
		  VpX += VpWidth;
		  ++it;
	  }
	  VpX = 0;
	  VpY += VpHeight;
  }*/

  auto it = objetos.begin();

  while (it != objetos.end())
  {
	  (*it)->render(camera->getViewMat());
	  ++it;
  }

}
//-------------------------------------------------------------------------

Diabolo* Scene::getDiabolo()
{
	return d;
}
//-------------------------------------------------------------------------

void Scene::update(GLuint timeElapsed)
{
	for (Entity* e : objetos)
		e->update(timeElapsed);
}