#pragma once
#include <glew.h>
#include "Array.h"

class Vertex
{
public:
	float x, y, z;
	Vertex();
	Vertex(float x, float y, float z);
};

class Mesh
{
public:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	int size;
	Mesh();
	Mesh(GLuint vao, GLuint vbo, GLuint ibo, int size);
	static Mesh create(Array<Vertex> vertices, Array<int> indices);
	static Mesh plane();
};

GLuint createVAO(GLuint vbo, GLuint ibo);
GLuint createVBO(Array<Vertex> vertices);
GLuint createIBO(Array<int> indices);

void bindMesh(Mesh& mesh);

void bindVAO(GLuint vao);
void bindVBO(GLuint vbo);
void bindIBO(GLuint ibo);
