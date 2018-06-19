#pragma once
#include <cinttypes>
#include <cmath>
class Vector2DInt
{
public:
	Vector2DInt(){}
	Vector2DInt(int x_, int y_) :x(x_), y(y_) {}
	Vector2DInt(float x_, float y_) :x(round(x_)), y(round(y_)) {}
	Vector2DInt(double x_, double y_):x(round(x_)), y(round(y_)) {}
	bool operator<(const Vector2DInt & left)const;
	int x = 0;
	int y = 0;
};