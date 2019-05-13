//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  //Mallas
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generateTriangleRGB(GLdouble r);
  static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generaDragon(GLuint numVert);
  static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
	  incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  static glm::dvec2 mover(GLdouble x, GLdouble y, GLdouble ang, GLdouble lon);
  static Mesh* generateRectangle(GLdouble w, GLdouble h);

  //Texturas
  static Mesh* generateRectangleTex(GLdouble w, GLdouble h, GLint divW, GLint divH);
  static Mesh* generateContCuboTex(GLdouble l);
  static Mesh* generateTriPyramidTex(GLdouble r, GLdouble h);

  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();

  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
   
protected:
	void enable();
	void disable();

   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;
   glm::dvec2* texCoords = nullptr;

   glm::dvec3* normals = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_