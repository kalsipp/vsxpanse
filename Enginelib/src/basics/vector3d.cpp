#include "vector3d.hpp"


Vector3D::Vector3D(double _x, double _y, double _z):
	x(_x), y(_y), z(_z) 
	{}

Vector3D::Vector3D(const Vector2D & other):
	x(other.x),
	y(other.y)
	{}

Vector3D Vector3D::operator+(const Vector3D&other)const {
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D & Vector3D::operator+=(const Vector3D & other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
Vector3D & Vector3D::operator+=(const Vector2D & other) {
	x += other.x;
	y += other.y;
	return *this;
}
Vector3D & Vector3D::operator-=(const Vector3D & other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}
Vector3D & Vector3D::operator-=(const Vector2D & other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector3D & Vector3D::operator*=(const Vector3D & other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

bool Vector3D::operator==(const Vector3D & other)const {
	bool equal = true;
	equal = x == other.x ? equal : false;
	equal = y == other.y ? equal : false;
	equal = y == other.y ? equal : false;
	return equal;
}

bool Vector3D::operator!=(const Vector3D & other) {
	return !((*this) == other);
}

void Vector3D::set(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Vector3D::rotate(const Vector3D & rot) {
	rotate_x(rot.x);
	rotate_y(rot.y);
	rotate_z(rot.z);
}

void Vector3D::rotate_around(const Vector3D & rot, const Vector3D & origin) {
	Vector3D tempVector(*this);
	tempVector -= origin;
	*this = origin;
	tempVector.rotate(rot);
	*this += tempVector;
}
void Vector3D::rotate_z(double degrees) {
	double radians = degrees * helpers::TO_RAD;
	double old_x = x;
	double old_y = y;
	x = (old_x * cos(radians)) - (old_y * sin(radians));
	y = (old_x * sin(radians)) + (old_y * cos(radians));
}

void Vector3D::rotate_y(double degrees) {
	double radians = degrees * helpers::TO_RAD;
	double old_x = x;
	double old_z = z;
	x = (old_x * cos(radians)) + (old_z * sin(radians));
	z = -(old_x * sin(radians)) + (old_z * cos(radians));
}
void Vector3D::rotate_x(double degrees) {
	double radians = degrees * helpers::TO_RAD;
	double old_y = y;
	double old_z = z;
	y = (old_y * cos(radians)) + (old_z * sin(radians));
	z = -(old_y * sin(radians)) + (old_z * cos(radians));
}


std::ostream & operator <<(std::ostream & stream, const Vector3D & p) {
	stream << "(" << p.x << "," << p.y << "," << p.z << ")";
	return stream;
}