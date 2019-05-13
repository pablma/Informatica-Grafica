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
  if (mesh != nullptr) 
    mesh -> draw();
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
	AngIni = mod(AngIni + 2 * timeElapsed, 360.0);
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
	draw();
}
//------------------------------------------------------------------------

rectangleTex::rectangleTex(GLdouble w, GLdouble h, GLint divW, GLint divH)
{
	mesh = Mesh::generateRectangleTex(w, h, divW, divH);
	texture.load("..\\Bmps\\baldosaC.bmp");
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
	mesh2 = Mesh::generateRectangleTex(l, l, 1, 1);
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
	mesh = Mesh::generateRectangleTex(w, h, w / 80, h / 80);
	texture.load("..\\Bmps\\Zelda.bmp");

	x = posX;
	y = posY;
}
//------------------------------------------------------------------------

void Photo::update(GLuint timeElapsed)
{
	texture.loadColorBuffer(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
	texture.load("..\\Bmps\\Screenshot.bmp");
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

	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
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

Grass::Grass(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ, GLint divW, GLint divH, GLdouble angle)
{
	mesh = Mesh::generateRectangleTex(w, h, 1, 1);
	glm::ivec3 Black = { 0, 0, 0 };
	texture.load("..\\Bmps\\grass.bmp", Black, 0);
	texture.wrap();
	x = posX;
	y = posY;
	z = posZ;
	angle_ = angle;
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

	aMat = rotate(aMat, radians(angle_), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));

	draw();
	texture.unbind();
	glDepthMask(GL_TRUE);
}