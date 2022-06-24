#include "Buffer.h"

Vertex::Vertex()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vertex::Vertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Mesh::Mesh()
{
	static Mesh p = plane();
	this->vao = p.vao;
	this->vbo = p.vbo;
	this->ibo = p.ibo;
	this->size = p.size;
}

Mesh::Mesh(GLuint vao, GLuint vbo, GLuint ibo, int size)
{
	this->vao = vao;
	this->vbo = vbo;
	this->ibo = ibo;
	this->size = size;
}

Mesh Mesh::create(Array<Vertex> vertices, Array<int> indices)
{
	GLuint vbo = createVBO(vertices);
	GLuint ibo = createIBO(indices);
	return Mesh(createVAO(vbo,ibo), vbo, ibo, indices.depth);
}

Mesh Mesh::plane()
{
	Array<Vertex> vertices;
	Array<int> indices;
	
	vertices.add(Vertex(0, 0, 0));
	vertices.add(Vertex(0, 0, 1));
	vertices.add(Vertex(1, 0, 1));
	vertices.add(Vertex(1, 0, 0));

	indices.add(0);
	indices.add(1);
	indices.add(2);
	indices.add(2);
	indices.add(3);
	indices.add(0);

	return Mesh::create(vertices, indices);
}

GLuint createVAO(GLuint vbo, GLuint ibo)
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	bindVAO(vao);
	bindVBO(vbo);
	bindIBO(ibo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 12, 0);

	return vao;
}

GLuint createVBO(Array<Vertex> vertices)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	bindVBO(vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.depth * 12, vertices.data, GL_STATIC_DRAW);
	return vbo;
}
GLuint createIBO(Array<int> indices)
{
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	bindIBO(ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.depth * 4, indices.data, GL_STATIC_DRAW);;
	return ibo;
}

void bindMesh(Mesh& mesh)
{
	bindVAO(mesh.vao);
	bindVBO(mesh.vbo);
	bindIBO(mesh.ibo);
}

void bindVAO(GLuint vao)
{
	glBindVertexArray(vao);
}
void bindVBO(GLuint vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void bindIBO(GLuint ibo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}
GLuint createIBO(Array<int> indices);