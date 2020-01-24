#pragma once

struct Vector {

	float x;
	float y;
	float z;

	Vector();
	Vector(float inX, float inY);
	Vector(float inX, float inY, float inZ);

	Vector&& operator + (const Vector& v);
};