//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "IndexMesh.h"
#include "Texture.h"
#include "Material.h"
#include "SpotLight.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };
  virtual void render(glm::dmat4 const& modelViewMat);
  virtual void update(GLuint timeElapsed);
  void setModelMat(glm::dmat4 const& mMat) { modelMat = mMat; }
  void setMaterial(Material const& mt) { material_ = mt; }
  void setTexture(Texture const& tex) { texture = tex; };
  glm::dmat4 getModelMat() { return modelMat; };
protected:
  Mesh* mesh = nullptr;
  Mesh* mesh2 = nullptr;
  IndexMesh* indexMesh_ = nullptr;
  Material material_;
  Texture texture;
  Texture texture2;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};


class TriangleRGB : public Entity
{
public:
	TriangleRGB(GLdouble r);
	~TriangleRGB() { };
	virtual void draw();
};
//-------------------------------------------------------------------------

class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};
//-------------------------------------------------------------------------

class TriPyramidTex : public Entity
{
public:
	TriPyramidTex(GLdouble r, GLdouble h);
	~TriPyramidTex() { };
	virtual void draw();
};
//-------------------------------------------------------------------------

class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo() { };
	virtual void draw();
};

class ContCuboTex : public Entity
{
public:
	ContCuboTex(GLdouble l);
	~ContCuboTex() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
		incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class Diabolo : public Entity
{
public:
	Diabolo(GLdouble r, GLdouble h, GLdouble posX, GLdouble posY);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed);
	void suma_ang();
private:
	GLdouble height;
	GLdouble AngIni = 0;
	GLdouble x;
	GLdouble y;
	GLdouble speed = 0.25;
};

//-------------------------------------------------------------------------

class rectangle : public Entity
{
public:
	rectangle(GLdouble w, GLdouble h);
	~rectangle() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class rectangleTex : public Entity
{
public:
	rectangleTex(GLdouble w, GLdouble h, GLint divW, GLint divH);
	~rectangleTex() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class Cubo : public Entity
{
public:
	Cubo(GLdouble l);
	~Cubo() { };
	virtual void draw();
	virtual void draw2();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble side;
	GLdouble ang = 40.0;
};

class CuboTex : public Entity
{
public:
	CuboTex(GLdouble l, GLdouble posX, GLdouble posY);
	~CuboTex() { };
	virtual void draw();
	virtual void draw2();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble side;
	GLdouble ang = 40.0;
	Texture cuboTex2;
	GLdouble x;
	GLdouble y;
};

class Suelo : public Entity
{
public:
	Suelo(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY);
	~Suelo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble x;
	GLdouble y;
};

class Photo : public Entity
{
public:
	Photo(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY);
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed);
	~Photo() { };
private:
	GLdouble x;
	GLdouble y;
};

class GlassPot : public Entity
{
public:
	GlassPot(GLdouble l, GLdouble posX, GLdouble posY, GLdouble posZ);
	~GlassPot() {};
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
};

class Grass : public Entity
{
public:
	Grass(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ);
	~Grass() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
};


class Sphere : public Entity
{
public:
	//Sphere(GLdouble w, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ);
	Sphere(GLdouble radio, GLdouble meridianos, GLdouble paralelos);
	~Sphere() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual SpotLight* getSpotLight();
protected:
	GLUquadricObj* sphere_;
	GLdouble radio_;
	GLdouble paralelos_;
	GLdouble meridianos_;
};


class LightSphere : public Sphere
{
public:
	LightSphere(GLdouble radio, GLdouble meridianos, GLdouble paralelos);
	~LightSphere() { };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed);
	virtual SpotLight* getSpotLight();
private:
	SpotLight* spotLight_;
	Sphere* sphere1_;
	Sphere* sphere2_;
	void renderSphere1(glm::dmat4 const& modelViewMat);
	void renderSphere2(glm::dmat4 const& modelViewMat);

	GLdouble Cx;
	GLdouble Cy;
	GLdouble Cz;
	glm::dvec3 trayectoria;
	GLdouble speed = 0.25;
	GLdouble AngIni = 0;
	Material LittleSphereMat_;
};


class Terrain : public Entity
{
public:
	Terrain();
	~Terrain() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

#endif //_H_Entities_H_