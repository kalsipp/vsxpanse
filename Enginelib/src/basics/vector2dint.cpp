#include "vector2dint.hpp"

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
