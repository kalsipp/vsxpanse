#include "pch.h"
#include "basics/vector2d.hpp"

TEST(vector2d, dot_basic)
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

TEST(vector2d, rotate_basic)
{
	{
		Vector2D vec1(1, 0);
		vec1.rotate(90);
		ASSERT_TRUE(vec1.equals(Vector2D(0, -1), 0.0001));
	}
	{
		Vector2D vec1(1, 0);
		vec1.rotate(180);
		ASSERT_TRUE(vec1.equals(Vector2D(-1, 0), 0.0001));
	}
	{
		Vector2D vec1(1, 0);
		vec1.rotate(90);
		vec1.rotate(90);
		ASSERT_TRUE(vec1.equals(Vector2D(-1, 0), 0.0001));
	}
}

TEST(vector2d, rotate_large_amounts)
{
	{
		Vector2D vec1(1, 0);
		vec1.rotate(180000); 
		ASSERT_TRUE(vec1.equals(Vector2D(1, 0), 0.000001));
	}
	{
		Vector2D vec1(1, 0);
		vec1.rotate(-180000);
		ASSERT_TRUE(vec1.equals(Vector2D(1, 0), 0.000001));
	}
	{
		Vector2D vec1(1, 0);
		for (int i = 0; i < 360*500; i++)
		{
			vec1.rotate(1);
		}
		ASSERT_TRUE(vec1.equals(Vector2D(1, 0), 0.000001));
	}
}