#pragma once
#include "math/Math.h"
#include "Buffer.h"
class Entity
{
public:
	Vector3f pos;
	Mesh mesh;
	Quaternion rotation;
	Entity();
	Entity(const Mesh& m);
	void update();
	void render();
	void move(float x, float y, float z);
	void move(Vector3f v);
	void rotate(Vector3f axis, float angle);
	Matrix4f getTransform();
};