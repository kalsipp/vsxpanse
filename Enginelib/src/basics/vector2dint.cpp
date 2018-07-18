#include "vector2dint.hpp"
#include "vector3d.hpp"
#include "vector2d.hpp"
#include "helpers.hpp"

Vector2DInt::Vector2DInt() {}
Vector2DInt::Vector2DInt(int x_, int y_) :x(x_), y(y_) {}
Vector2DInt::Vector2DInt(float x_, float y_) :x(helpers::round_to_int(x_)), y(helpers::round_to_int(y_)) {}
Vector2DInt::Vector2DInt(double x_, double y_) :x(helpers::round_to_int(x_)), y(helpers::round_to_int(y_)) {}
Vector2DInt::Vector2DInt(const Vector2D & vec) : x(helpers::round_to_int(vec.x)), y(helpers::round_to_int(vec.y)) {}
Vector2DInt::Vector2DInt(const Vector3D & vec) : x(helpers::round_to_int(vec.x)), y(helpers::round_to_int(vec.y)) {}

bool Vector2DInt::operator<(const Vector2DInt & left)const
{
	uint64_t left_val = left.x;
	left_val = left_val << 32;
	left_val |= left.y;
	uint64_t right_val = x;
	right_val = right_val << 32;
	right_val |= y;
	return left_val < right_val;
}


bool Vector2DInt::operator==(const Vector2DInt & other)const
{
	return (other.y == y) && (other.x == x);
}
Vector2DInt Vector2DInt::operator*(const int & val)
{
	return Vector2DInt(x*val, y*val);
}
Vector2DInt& Vector2DInt::operator+=(const Vector2DInt & other)
{
	x += other.x;
	y += other.y;
	return *this;
}