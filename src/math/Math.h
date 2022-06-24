#pragma once
#include <cmath>

class Vector3f
{
public:
	float x, y, z;
	inline Vector3f()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	inline Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	inline Vector3f operator+(Vector3f v)
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}
	inline Vector3f operator*(Vector3f& v)
	{
		return Vector3f(x * v.x, y * v.y, z * v.z);
	}
	inline Vector3f operator*(float v)
	{
		return Vector3f(x * v, y * v, z * v);
	}
	inline float dot(Vector3f& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	inline Vector3f cross(Vector3f& v)
	{
		return Vector3f(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x *	v.y - y * v.x
		);
	}
};

class Quaternion
{
public:
	float x, y, z, w;
	inline Quaternion()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}
	inline Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	inline Quaternion setAxisAngle(Vector3f axis, float angle)
	{
		float sinHalfAngle = sinf(angle * 0.5f);
		float cosHalfAngle = cosf(angle * 0.5f);
		this->x = axis.x * sinHalfAngle;
		this->y = axis.y * sinHalfAngle;
		this->z = axis.z * sinHalfAngle;
		this->w = cosHalfAngle;

		return *this;
	}
	inline Quaternion setEuler(Vector3f rotation)
	{
		float cx = cosf(rotation.x * 0.5f);
		float cy = cosf(rotation.y * 0.5f);
		float cz = cosf(rotation.z * 0.5f);

		float sx = sinf(rotation.x * 0.5f);
		float sy = sinf(rotation.y * 0.5f);
		float sz = sinf(rotation.z * 0.5f);

		this->x = cx * sy * sz + cy * cz * sx;
		this->y = cz * cz * sy - cy * sx * sz;
		this->z = cx * cy * sz - cy * sx * sy;
		this->w = sx * sy * sz + cx * cy * cz;

		return *this;
	}
	inline float magnitude()
	{
		return 1.0f / sqrtf(magnitudeSquared());
	}
	inline float magnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}
	inline Quaternion& normalize()
	{
		float inv = sqrtf(magnitudeSquared());
		this->x *= inv;
		this->y *= inv;
		this->z *= inv;
		this->w *= inv;
		return *this;
	}
	inline Quaternion normalized()
	{
		float inv = sqrtf(magnitudeSquared());
		return Quaternion(x * inv, y * inv, z * inv, w * inv);
	}
	inline float dot(Quaternion& q)
	{
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}
	inline Quaternion operator*(const Quaternion& q)
	{
		return Quaternion(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x,
			w * q.w - x * q.x - y * q.y - z * q.z);
	}
	inline Vector3f operator*(Vector3f& v)
	{
		Vector3f q(x, y, z);
		return q * q.dot(v) * 2.0f + v * (w * w - q.dot(v)) + (q.cross(v) * w * 2.0f);
	}
};
inline Quaternion AxisAngle(Vector3f axis, float angle)
{
	return Quaternion().setAxisAngle(axis, angle);
}

class Matrix4f
{
public:
	union
	{
		float elements[16]{};
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
	};
	inline Matrix4f()
	{
		m00 = 1.0f;
		m11 = 1.0f;
		m22 = 1.0f;
		m33 = 1.0f;
	}
	inline Matrix4f operator*(Matrix4f m)
	{
		Matrix4f e;
		e.m00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30;
		e.m01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31;
		e.m02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32;
		e.m03 = m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33;

		e.m10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30;
		e.m11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
		e.m12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
		e.m13 = m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

		e.m20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30;
		e.m21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
		e.m22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
		e.m23 = m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

		e.m30 = m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30;
		e.m31 = m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
		e.m32 = m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
		e.m33 = m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33;
		return e;
	}
};

inline Matrix4f Translate(Vector3f t)
{
	Matrix4f m;
	m.m30 = t.x;
	m.m31 = t.y;
	m.m32 = t.z;
	return m;
}

inline Matrix4f Scale(Vector3f t)
{
	Matrix4f m;
	m.m00 = t.x;
	m.m11 = t.y;
	m.m22 = t.z;
	return m;
}

inline Matrix4f Rotation(Quaternion q)
{
	Matrix4f m;
	m.m00 = 1.0f - 2.0f * ((q.y * q.y) + (q.z * q.z));
	m.m01 = 2.0f * ((q.x * q.y) + (q.z * q.w));
	m.m02 = 2.0f * ((q.x * q.z) - (q.y * q.w));
	m.m10 = 2.0f * ((q.x * q.y) - (q.z * q.w));
	m.m11 = 1.0f - 2.0f * ((q.x * q.x) + (q.z * q.z));
	m.m12 = 2.0f * ((q.y * q.z) + (q.x * q.w));
	m.m20 = 2.0f * ((q.x * q.z) + (q.y * q.w));
	m.m21 = 2.0f * ((q.y * q.z) - (q.x * q.w));
	m.m22 = 1.0f - 2.0f * ((q.x * q.x) + (q.y * q.y));

	return m;
}

inline Matrix4f Perspective(float fov, float aspect, float near, float far)
{
	float f = fov * (3.14f / 180.0f);
	Matrix4f m;
	m.m00 = 1 / (aspect * tanf(f / 2));
	m.m11 = 1 / (tanf(f / 2));
	m.m22 = -(far + near) / (far - near);
	m.m23 = -1;
	m.m32 = (2 * far * near) / (far - near);
	return m;
}
