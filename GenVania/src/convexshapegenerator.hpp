#pragma once
#include <vector>
#include "basics/vector2d.hpp"

class ConvexShapeGenerator
{
public:
	static void get_convex_shape(std::vector<Vector2D>& out_container, const Vector2D& boundaries);
};