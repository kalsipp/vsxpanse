#include "pch.h"
#include "basics/vector2d.hpp"

TEST(dot, test)
{
	{
		Vector2D vec1(1, 2);
		Vector2D vec2(3, 4);
		double result = vec1.dot(vec2);
		ASSERT_EQ(result, 11);
	}
	{
		Vector2D vec1(2134, -123);
		Vector2D vec2(-534, 2124);
		double result = vec1.dot(vec2);
		ASSERT_EQ(result, -1400808);

	}
}