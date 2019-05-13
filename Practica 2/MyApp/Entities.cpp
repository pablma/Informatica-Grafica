#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
	//material_.load();
  if (mesh != nullptr) 
    mesh->draw();
}
//-------------------------------------------------------------------------


void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

void Entity::update(GLuint tiemElapsed)
{

}

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangleRGB(r);
}
//-------------------------------------------------------------------------

void TriangleRGB::draw()
{
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void TriPyramid::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//-------------------------------------------------------------------------

TriPyramidTex::TriPyramidTex(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h);
	texture.load("..\\Bmps\\floris.bmp");
}


void TriPyramidTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}
//-------------------------------------------------------------------------

void ContCubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//-------------------------------------------------------------------------

ContCuboTex::ContCuboTex(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCuboTex(l);
	texture.load("..\\Bmps\\Zelda.bmp");
}
//-------------------------------------------------------------------------

void ContCuboTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind();
	mesh->draw();
	texture.unbind();
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}
//-------------------------------------------------------------------------

void Dragon::draw()
{
	glPointSize(2.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//-------------------------------------------------------------------------

void Dragon::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);

	glm::dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(-40.0, -170.0, 0.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 1.0));

	glLoadMatrixd(value_ptr(aMat));
	draw();
}
//------------------------------------------------------------------------

Poliespiral::Poliespiral(glm::dvec2  verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}
//-------------------------------------------------------------------------

void Poliespiral::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//------------------------------------------------------------------------

void Poliespiral::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;

	aMat = scale(aMat, dvec3(10.0, 10.0, 1.0));

	glLoadMatrixd(value_ptr(aMat));
	draw();
}
//------------------------------------------------------------------------

Diabolo::Diabolo(GLdouble r, GLdouble h, GLdouble posX, GLdouble posY) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(r, h);
	texture.load("..\\Bmps\\floris.bmp");
	height = h;
	x = posX;
	y = posY;
}
//------------------------------------------------------------------------

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void Diabolo::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;

	texture.bind();

	aMat = translate(aMat, dvec3(x, y, 0.0));
	aMat = rotate(aMat, radians(AngIni), dvec3(0.0, 0.0, 1.0));

	aMat = translate(aMat, dvec3(0.0, 0.0, -height));	
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));	
	draw();

	aMat = translate(aMat, dvec3(0.0, 0.0, height * 2));
	aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	
	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));	
	draw();
	
	texture.unbind();	
}
//------------------------------------------------------------------------

void Diabolo::update(GLuint timeElapsed)
{
	AngIni = mod(AngIni + speed * timeElapsed, 360.0);
}
//------------------------------------------------------------------------

void Diabolo::suma_ang()
{
	AngIni += 7;
}
//------------------------------------------------------------------------

rectangle::rectangle(GLdouble w, GLdouble h)
{
	mesh = Mesh::generateRectangle(w, h);
}
//------------------------------------------------------------------------

void rectangle::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//------------------------------------------------------------------------

void rectangle::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
}
//------------------------------------------------------------------------

rectangleTex::rectangleTex(GLdouble w, GLdouble h, GLint divW, GLint divH)
{
	mesh = Mesh::generateRectangleTex(w, h, divW, divH);
	texture.load("..\\Bmps\\Zelda.bmp");
}
//------------------------------------------------------------------------

void rectangleTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();

}
//------------------------------------------------------------------------

void rectangleTex::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	texture.bind();
	draw();
	texture.unbind();
}
//------------------------------------------------------------------------

Cubo::Cubo(GLdouble l)
{
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangle(l, l);
	side = l;
}
//------------------------------------------------------------------------

void Cubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}
//------------------------------------------------------------------------

void Cubo::draw2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh2->draw();
}
//------------------------------------------------------------------------

void Cubo::render(glm::dmat4 const& modelViewMat)
{
	
	glMatrixMode(GL_MODELVIEW);


	glm::dmat4 aMat = modelViewMat * modelMat;
	
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = translate(aMat, dvec3(0.0, -side / 2, 0.0));
	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(aMat));
	draw2();

	//Comando para devolver la matriz a su estado inicial
	aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(0.0, side, 0.0));

	aMat = translate(aMat, dvec3(0.0, 0.0, (-(side / 2) + (side / 2) * sin(radians(ang)))));

	aMat = translate(aMat, dvec3(0.0, - ((side / 2) - ((side / 2 ) * cos(radians(ang)))), 0.0));
	aMat = rotate(aMat, radians(ang), dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(aMat));
	draw2();

}
//------------------------------------------------------------------------

CuboTex::CuboTex(GLdouble l, GLdouble posX, GLdouble posY)
{
	mesh = Mesh::generateContCuboTex(l);
	mesh2 = Mesh::generateRectangleTex(l, l, 0, 0);
	texture.load("..\\Bmps\\container2.bmp");
	cuboTex2.load("..\\Bmps\\lego.bmp");
	side = l;

	x = posX;
	y = posY;
}
//------------------------------------------------------------------------

void CuboTex::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void CuboTex::draw2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh2->draw();
}
//------------------------------------------------------------------------

void CuboTex::render(glm::dmat4 const& modelViewMat)
{

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);

	glm::dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(x, y, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	
	glCullFace(GL_BACK);
	texture.bind();
	draw();
	texture.unbind();

	glCullFace(GL_FRONT);
	cuboTex2.bind();
	draw();
	cuboTex2.unbind();

	//TAPA DE ABAJO
	aMat = translate(aMat, dvec3(0.0, -side / 2, 0.0));
	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));


	glLoadMatrixd(value_ptr(aMat));
	glCullFace(GL_BACK);
	texture.bind();
	draw2();
	texture.unbind();

	glCullFace(GL_FRONT);
	cuboTex2.bind();
	draw2();
	cuboTex2.unbind();

	//Comando para devolver la matriz a su estado inicial
	aMat = modelViewMat * modelMat;

	//TAPA DE ARRIBA
	aMat = translate(aMat, dvec3(x, y, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	aMat = translate(aMat, dvec3(0.0, side, 0.0));

	aMat = translate(aMat, dvec3(0.0, 0.0, (-(side / 2) + (side / 2) * sin(radians(ang)))));

	aMat = translate(aMat, dvec3(0.0, -((side / 2) - ((side / 2) * cos(radians(ang)))), 0.0));
	aMat = rotate(aMat, radians(ang), dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(aMat));
	
	glCullFace(GL_BACK);
	cuboTex2.bind();
	draw2();
	cuboTex2.unbind();

	glCullFace(GL_FRONT);
	texture.bind();
	draw2();

	glDisable(GL_CULL_FACE);
	texture.unbind();
}
//------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY)
{
	mesh = Mesh::generateRectangleTex(w, h, w / 80, h / 80);
	texture.load("..\\Bmps\\baldosaC.bmp");

	x = posX;
	y = posY;
}
//------------------------------------------------------------------------

void Suelo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void Suelo::render(glm::dmat4 const& modelViewMat)
{

	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	texture.bind();

	aMat = translate(aMat, dvec3(x, y, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	
	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	
	draw();
	texture.unbind();
}
//------------------------------------------------------------------------

Photo::Photo(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY)
{
	mesh = Mesh::generateRectangleTex(w, h, 0, 0);
	texture.load("..\\Bmps\\Zelda.bmp");

	x = posX;
	y = posY;
}
//------------------------------------------------------------------------

void Photo::update(GLuint timeElapsed)
{
	texture.loadColorBuffer(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
}
//------------------------------------------------------------------------

void Photo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void Photo::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	texture.bind();

	aMat = translate(aMat, dvec3(x, y, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	aMat = rotate(aMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();
	texture.unbind();
}
//------------------------------------------------------------------------

GlassPot::GlassPot(GLdouble l, GLdouble posX, GLdouble posY, GLdouble posZ)
{
	mesh = Mesh::generateContCuboTex(l);
	texture.load("..\\Bmps\\window.bmp", 100);
	x = posX;
	y = posY;
	z = posZ;
}
//------------------------------------------------------------------------

void GlassPot::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void GlassPot::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glDepthMask(GL_FALSE);
	texture.bind();

	aMat = translate(aMat, dvec3(x, y, z));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	texture.unbind();
	glDepthMask(GL_TRUE);
}
//------------------------------------------------------------------------

Grass::Grass(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ)
{
	mesh = Mesh::generateRectangleTex(w, h, 0, 0);
	glm::ivec3 Black = { 0, 0, 0 };
	texture.load("..\\Bmps\\grass.bmp", Black, 0);
	texture.wrap();
	x = posX;
	y = posY;
	z = posZ;
}
//------------------------------------------------------------------------

void Grass::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//------------------------------------------------------------------------

void Grass::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glDepthMask(GL_FALSE);
	texture.bind();

	aMat = translate(aMat, dvec3(x, y, z));
	glLoadMatrixd(value_ptr(aMat));

	aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	aMat = rotate(aMat, radians(90.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();

	texture.unbind();
	glDepthMask(GL_TRUE);
}
//------------------------------------------------------------------------


Sphere::Sphere(GLdouble radio, GLdouble meridianos, GLdouble paralelos)
{
	sphere_ = gluNewQuadric();

	gluQuadricDrawStyle(sphere_, GLU_FILL);
	gluQuadricNormals(sphere_, GLU_SMOOTH);
	gluQuadricOrientation(sphere_, GLU_OUTSIDE);
	gluQuadricTexture(sphere_, GL_TRUE);

	radio_ = radio;
	meridianos_ = meridianos;
	paralelos_ = paralelos;
}


void Sphere::draw()
{
	texture.bind(GL_MODULATE);
	material_.load();
	gluSphere(sphere_, radio_, meridianos_, paralelos_);
	texture.unbind();
}
//------------------------------------------------------------------------


SpotLight* Sphere::getSpotLight()
{
	return 0;
}
//------------------------------------------------------------------------


void Sphere::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	draw();
}
//------------------------------------------------------------------------


LightSphere::LightSphere(GLdouble radio, GLdouble meridianos, GLdouble paralelos) : Sphere(radio, meridianos, paralelos)
{
	spotLight_ = new SpotLight();

	spotLight_->setAlpha(30.0);
	spotLight_->setPos(dvec3(0.0, 0.0, 0.0));
	spotLight_->setLightDirection(0.0, -1.0, 0.0);

	texture2.load("..\\Bmps\\Zelda.bmp");
	LittleSphereMat_.setSilver();

	sphere1_ = new Sphere(radio / 2.0, meridianos / 2.0, paralelos / 2.0);
	sphere1_->setTexture(texture2);
	sphere1_->setMaterial(LittleSphereMat_);
	sphere1_->setModelMat(modelMat);
	sphere2_ = new Sphere(radio / 2.0, meridianos / 2.0, paralelos / 2.0);
	sphere2_->setTexture(texture2);
	sphere2_->setMaterial(LittleSphereMat_);
	sphere2_->setModelMat(modelMat);

	Cx = 512;
	Cy = 100;
	Cz = -Cx;
}
//------------------------------------------------------------------------


void LightSphere::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;

	// Animación de giro
	aMat = translate(aMat, trayectoria);
	aMat = rotate(aMat, radians(AngIni), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	spotLight_->load(aMat);	// Cargar la luz

	draw();
	renderSphere1(aMat);
	renderSphere2(aMat);
}
//------------------------------------------------------------------------


void LightSphere::update(GLuint timeElapsed)
{
	trayectoria = dvec3(Cx * cos(radians(AngIni)), Cy * sin(radians(AngIni)) * sin(radians(AngIni)), Cz * sin(radians(AngIni)) * cos(radians(AngIni)));
	AngIni = mod(AngIni + speed * timeElapsed, 360.0);
}


void LightSphere::renderSphere1(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	//glm::dmat4 aMat = modelViewMat; // *sphere1_->modelMat;   para que funcionase habría que multiplicar la modelViewMat por la matriz de la propia esfera
	glm::dmat4 aMat = modelViewMat * sphere1_->getModelMat();
	aMat = translate(aMat, dvec3(radio_+ (radio_ / 2.0), 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	sphere1_->draw();
}
//------------------------------------------------------------------------


void LightSphere::renderSphere2(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	//glm::dmat4 aMat = modelViewMat; // *sphere2_->modelMat;
	glm::dmat4 aMat = modelViewMat * sphere2_->getModelMat();
	aMat = translate(aMat, dvec3(-radio_ - (radio_ / 2.0), 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	sphere2_->draw();
}
//------------------------------------------------------------------------


SpotLight* LightSphere::getSpotLight()
{
	return spotLight_;
}
//------------------------------------------------------------------------


Terrain::Terrain()
{
	indexMesh_ = IndexMesh::generateTerrain();
}
//------------------------------------------------------------------------


void Terrain::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind(GL_MODULATE);
	material_.load();
	indexMesh_->draw();
	texture.unbind();
}
//------------------------------------------------------------------------


void Terrain::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	draw();
}
//------------------------------------------------------------------------