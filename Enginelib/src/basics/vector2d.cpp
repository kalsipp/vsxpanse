#include "vector2d.hpp"


Vector2D::Vector2D() {}
Vector2D::Vector2D(double _x, double _y): x(_x), y(_y) {}
Vector2D::Vector2D(const Vector3D & vec): x(vec.x), y(vec.y) {}
Vector2D & Vector2D::operator=(const Vector3D & other){
	x = other.x;
	y = other.y;
	return *this;
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