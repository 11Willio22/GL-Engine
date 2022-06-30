#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const Mesh& m)
{
	this->mesh = m;
}

void Entity::update()
{

}

void Entity::render()
{

}

void Entity::move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}


void Entity::move(Vector3f v)
{
	pos = pos + v;
}

void Entity::rotate(Vector3f axis, float angle)
{
	this->rotation = this->rotation * AxisAngle(axis, angle);
}

Matrix4f Entity::getTransform()
{
	return Rotation(rotation) * Translate(pos);
}

