#include "BaseStructs\Vector.hpp"

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(float inX, float inY)
{
	x = inX;
	y = inY;
	z = 0;
}

Vector::Vector(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;
}

Vector&& Vector::operator+(const Vector& v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}
