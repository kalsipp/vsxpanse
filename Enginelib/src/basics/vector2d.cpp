#include "vector2d.hpp"
#include "vector2dint.hpp"
#include "vector3d.hpp"

Vector2D::Vector2D() {}
Vector2D::Vector2D(double _x, double _y): x(_x), y(_y) {}
Vector2D::Vector2D(const Vector3D & vec): x(vec.x), y(vec.y) {}
Vector2D::Vector2D(const Vector2DInt & vec): x(vec.x), y(vec.y){}
Vector2D & Vector2D::operator=(const Vector3D & other){
	x = other.x;
	y = other.y;
	return *this;
}
Vector2D & Vector2D::operator+=(const Vector2D & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D & other)const
{
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator+(const Vector2D & other)const
{
	return Vector2D(x + other.x, y + other.y);
}

double Vector2D::magnitude()const
{
	return sqrt(x*x + y*y);
}

double Vector2D::magnitude_squared() const
{
	return x * x + y * y;
}

double Vector2D::dot(const Vector2D& other) const
{
	return x * other.x + y * other.y;
}

void Vector2D::rotate_around(double angle, const Vector2D pivot_point)
{
	angle = helpers::TO_RAD*angle;
	const double angle_sin = sin(angle);
	const double angle_cos = cos(angle);
	x -= pivot_point.x;
	y -= pivot_point.y;
	const double xnew = x*angle_cos - y*angle_sin;
	const double ynew = x*angle_sin + y*angle_cos;
	x = xnew + pivot_point.x;
	y = ynew + pivot_point.y;
}

void Vector2D::rotate(double angle)
{
	angle = helpers::TO_RAD*angle;
	double oldX = x;
	x = x*cos(angle) + y*sin(angle);
	y = y*cos(angle) - oldX*sin(angle);
}

Vector2D Vector2D::perpendicular() const
{
	return Vector2D(-y, x);
}

Vector2D Vector2D::normalized() const
{
	const double magn = magnitude();
	return Vector2D(x/magn, y/magn);
}

void Vector2D::set(double _x, double _y) {
	x = _x;
	y = _y;
}

void Vector2D::round_to_int(){
	x = double(round(x));
	y = double(round(y));
}

SDL_Point Vector2D::get_sdl_point() {
	return SDL_Point{int(round(x)), int(round(y))};
}
std::ostream & operator <<(std::ostream & stream, const Vector2D & p){
	stream << "(" << p.x << "," << p.y << ")";
	return stream;
}