#pragma once
#include <SDL.h>
#include <iostream>
#include <cmath>
#include "vector3d.hpp"
class Vector3D;
class Vector2D {
public:
	Vector2D();
	Vector2D(double x, double y=0);
	Vector2D(const Vector3D &);
	Vector2D & operator=(const Vector3D &);
	void set(double, double);
	void round_to_int();
	SDL_Point get_sdl_point();
	double x = 0;
	double y = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Vector2D &);
private:

};