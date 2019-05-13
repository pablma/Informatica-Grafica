#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH); // Gouraud Shading
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  camera->setAZ();
  
  // Establezco el tamaño del ViewPort
  VpWidth = camera->getVP()->getW() / 2;
  VpHeight = camera->getVP()->getH() / 2;

  // lights
  cameraLight_ = new SpotLight();
  cameraLight_->setAlpha(10.0);
  lights_.push_back(cameraLight_);

  directionalLight_ = new Light();
  directionalLight_->setDir(glm::fvec3(0.0, 0.0, -1.0));	//Luz direccional en el eje z
  lights_.push_back(directionalLight_);

  // textures  
  moonText_.load("..\\Bmps\\moon.bmp");
  SunText_.load("..\\Bmps\\sun.bmp");
  MarsText_.load("..\\Bmps\\mars.bmp");
  VenusText_.load("..\\Bmps\\venus.bmp");
  TerrainText_.load("..\\Bmps\\BarrenReds.bmp");

  // materials
  bronzeMat_.setBronze();
  ChromeMat_.setChrome();
  SilverMat_.setSilver();
  CopperMat_.setCopper();

  // Matrix
  moonMatrix_ = glm::translate(moonMatrix_, glm::dvec3(150.0, 350.0, 0.0));
  sunMatrix_ = glm::translate(sunMatrix_, glm::dvec3(-150.0, 250.0, 0.0));
  marsMatrix_ = glm::translate(marsMatrix_, glm::dvec3(150.0, 100.0, 0.0));

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
  //objetos.push_back(new rectangleTex(150.0, 150.0, 0, 0));
  //objetos.push_back(new TriPyramidTex(150.0, 150.0));
  //objetos.push_back(new ContCuboTex(150.0));

  // ESCENA PRACTICA 1
  /*objetos.push_back(new Suelo(500.0, 500.0, 0.0, -150.0));

  photo_ = new Photo(100.0, 100.0, 100.0, -149.0);
  objetos.push_back(photo_);
  
  objetos.push_back(new Grass(150.0, 150.0, 150.0, -75.0, -150.0));
  objetos.push_back(new GlassPot(100.0, 150.0, -100.0, -150.0));

  diabolo_ = new Diabolo(75.0, 75.0, 200, 100);
  objetos.push_back(diabolo_);

  objetos.push_back(new CuboTex(100.0, 0.0, -100.0));*/


  // ESCENA PRACTICA 2
  terrain_ = new Terrain();
  terrain_->setTexture(TerrainText_);
  terrain_->setMaterial(SilverMat_);
  objetos.push_back(terrain_);

  sunSphere_ = new Sphere(100, 100, 100);
  sunSphere_->setTexture(SunText_);
  sunSphere_->setMaterial(ChromeMat_);
  sunSphere_->setModelMat(sunMatrix_);
  objetos.push_back(sunSphere_);

  moonSphere_ = new LightSphere(50, 50, 50);
  moonSphere_->setTexture(moonText_);
  moonSphere_->setMaterial(SilverMat_);
  moonSphere_->setModelMat(moonMatrix_);
  objetos.push_back(moonSphere_);

  marsSphere_ = new Sphere(75, 75, 75);
  marsSphere_->setTexture(MarsText_);
  marsSphere_->setMaterial(bronzeMat_);
  marsSphere_->setModelMat(marsMatrix_);
  objetos.push_back(marsSphere_);

  // Para obtener la luz de LightSphere
  lights_.push_back(moonSphere_->getSpotLight());
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

  // Foco de la cámera
  glm::fvec3 lightPos = { camera->getX(), camera->getY(), camera->getZ()};
  cameraLight_->setPos(lightPos);
  cameraLight_->setLightDirection(camera->getDirX(), camera->getDirY(), camera->getDirZ());
  
  cameraLight_->load(camera->getViewMat());

  // Luz direccional
  directionalLight_->load(camera->getViewMat());

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
	return diabolo_;
}
//-------------------------------------------------------------------------

Photo* Scene::getPhoto()
{
	return photo_;
}
//-------------------------------------------------------------------------


Light* Scene::getDirectionalLight_()
{
	return directionalLight_;
}
//-------------------------------------------------------------------------


void Scene::update(GLuint timeElapsed)
{
	for (Entity* e : objetos)
		e->update(timeElapsed);
}
//-------------------------------------------------------------------------


std::vector<Light*> Scene::getLights()
{
	return lights_;
}