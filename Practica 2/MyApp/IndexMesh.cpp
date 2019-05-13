#include "IndexMesh.h"
#include <fstream>
#include <iostream>


IndexMesh::IndexMesh()
{
	numIndices = 0;
	indices = nullptr;
	type = GL_TRIANGLES;
}


IndexMesh::~IndexMesh()
{
	delete[] indices;
}


void IndexMesh::enable()
{
	Mesh::enable();
	if (indices != nullptr) 
	{
		glEnableClientState(GL_INDEX_ARRAY);
		glIndexPointer(GL_UNSIGNED_INT, 0, indices);
	}
}


void IndexMesh::disable()
{
	Mesh::disable();
	glDisableClientState(GL_INDEX_ARRAY);
}


void IndexMesh::draw()
{
	enable();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);
	disable();
}


IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint numDiv)
{
	IndexMesh* m = new IndexMesh();
	GLdouble incr = lado / numDiv;	// incremento para la coordenada x, y la z
	GLuint numVer = numDiv + 1;	// num. de vértices por filas y por columnas

	GLdouble x, z;
	z = -lado / 2;

	GLuint ind = 0;	// Me señala los índices para formar los triángulos
	GLuint vi;

	// generar vértices
	m->numIndices = numDiv * numDiv * 6;
	m->indices = new GLuint[m->numIndices];
	m->numVertices = numVer * numVer;
	m->vertices = new glm::dvec3[m->numVertices];


	for (GLuint i = 0; i < numVer; i++)
	{
		x = -lado / 2;

		for (GLuint j = 0; j < numVer; j++)
		{
			m->vertices[i * numVer + j] = glm::dvec3(x, 0, z);
			x += incr;
		}

		z += incr;
	}


	for (GLuint i = 0; i < numDiv; i++)
	{
		for (GLuint j = 0; j < numDiv; j++)
		{
			vi = i * numVer + j;

			// Primer triángulo
			m->indices[ind++] = vi;
			m->indices[ind++] = vi + numVer;
			m->indices[ind++] = vi + 1;

			// Segundo triángulo
			m->indices[ind++] = vi + 1;
			m->indices[ind++] = vi + numVer;
			m->indices[ind++] = vi + numVer + 1;		
		}
	}

	return m;
}


IndexMesh* IndexMesh::generateTerrain()
{
	std::ifstream file("..\\Bmps\\terrain.raw", std::ios::binary); // open
	if (!file.is_open()) return nullptr; // "terrain.raw": 257*257 unsigned chars

	GLuint nDiv = 256; // numVer = 257.
	GLdouble lado = nDiv * 8; // para incr=8
	
	IndexMesh* m = generateGrid(lado, nDiv);
	
	unsigned char * data = new unsigned char[m->numVertices];
	file.read((char *)data, m->numVertices * sizeof(char));
	file.close(); 
	// char = byte -> leer en data un bloque de numVertices bytes

	// modificar la coordenada Y de los vértices con los datos de data (*0.5)
	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i].y = data[i] * 0.5;
	}


	// generar coordenadas de textura -> recorrido de vértices
	// generar coordenadas de textura
	int z = 0;
	m->texCoords = new glm::dvec2[m->numVertices];
	for (GLuint i = 0; i < nDiv + 1; i++)
	{
		for (GLuint j = 0; j < nDiv + 1; j++)
		{
			m->texCoords[z++] = glm::dvec2(j * 1.0/nDiv, i * 1.0/nDiv);
		}
	}

	delete data;

	// generar normales
	glm::dvec3 n;
	glm::dvec3 a;
	glm::dvec3 b;
	glm::dvec3 c;

	m->normals = new glm::dvec3[m->numVertices];

	for (GLuint i = 0; i < m->numVertices; i++)	//Ponemos el vector de normales a 0
	{
		m->normals[i].x = 0;
		m->normals[i].y = 0;
		m->normals[i].z = 0;
	}

	for (GLuint i = 0; i < m->numIndices; i += 3)
	{
		a = m->vertices[m->indices[i]];
		b = m->vertices[m->indices[i + 1]];
		c = m->vertices[m->indices[i + 2]];

		//a = { m->vertices[i].x, m->vertices[i].y, m->vertices[i].z };
		//b = { m->vertices[i + 1].x, m->vertices[i + 1].y, m->vertices[i + 1].z };
		//c = { m->vertices[i + 2].x, m->vertices[i + 2].y, m->vertices[i + 2].z };
		
		n = glm::normalize(glm::cross(b - a, c - a));

		m->normals[m->indices[i]] += n;
		m->normals[m->indices[i + 1]] += n;
		m->normals[m->indices[i + 2]] += n;
	}

	for (GLuint i = 0; i < m->numVertices; i++)
	{
		glm::normalize(m->normals[i]);
	}

	return m;
}
