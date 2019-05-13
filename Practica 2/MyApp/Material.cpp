#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}


void Material::load()
{
	glMaterialfv(face, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	
	//glMaterialfv(face, GL_EMISSION, glm::value_ptr(glm::fvec4(0.0, 0.0, 1.0, 1.0)));	//El material emitiría luz
	
	glShadeModel(sh);
}


void Material::setBronze()
{
	ambient = {0.2125, 0.1275, 0.054, 1.0};
	diffuse = { 0.714, 0.4284, 0.18144, 1.0 };
	specular = { 0.393548, 0.271906, 0.166721, 1.0 };
	expF = 25.6;
}


void Material::setChrome()
{
	ambient = { 0.25, 0.25, 0.25, 1.0 };
	diffuse = { 0.4, 0.4, 0.4, 1.0 };
	specular = { 0.774597, 0.774597, 0.774597, 1.0 };
	expF = 76.8;
}


void Material::setSilver()
{
	ambient = { 0.19225, 0.19225, 0.19225, 1.0 };
	diffuse = { 0.50754, 0.50754, 0.50754, 1.0 };
	specular = { 0.508273, 0.508273, 0.508273, 1.0 };
	expF = 51.2;
}


void Material::setCopper()
{
	ambient = { 0.19125, 0.0735, 0.0225, 1.0 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1.0 };
	specular = { 0.256777, 0.137622, 0.086014, 1.0 };
	expF = 12.8;
}