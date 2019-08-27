
#include "pch.h"

#include "basics/helpers.hpp"
#include "basics/vector2dint.hpp"
#include "basics/vector2d.hpp"

TEST(random_int, limits)
{
	const int min = 1;
	const int max = 2;
	for (int i = 0; i < 100; ++i) {
		int res = helpers::random_int(min, max);

		ASSERT_TRUE(res >= min);
		ASSERT_TRUE(res <= max);
	}
}
TEST(random_int, randomness)
{
	const int min = 0;
	const int max = 100;
	int32_t sum = 0;
	double expected_avg = (max-min)/2;
	int iters = 1000;
	for (int i = 0; i < iters; ++i) {
		sum += helpers::random_int(min, max);
	}
	double realavg = sum / iters;
	std::cout << std::to_string(realavg) << std::endl;
	ASSERT_NEAR(expected_avg, realavg, 2.0);
}
TEST(random_int, negative)
{
	const int min = -100;
	const int max = 100;
	int32_t sum = 0;
	double expected_avg = 0;
	int iters = 1000;
	for (int i = 0; i < iters; ++i) {
		sum += helpers::random_int(min, max);
	}
	double realavg = sum / iters;
	std::cout << std::to_string(realavg) << std::endl;
	ASSERT_NEAR(expected_avg, realavg, 5.0);
}
TEST(random_int, both_negative)
{
	const int min = -200;
	const int max = -100;
	int32_t sum = 0;
	double expected_avg = -150;
	int iters = 1000;
	for (int i = 0; i < iters; ++i) {
		sum += helpers::random_int(min, max);
	}
	double realavg = sum / iters;
	std::cout << std::to_string(realavg) << std::endl;
	ASSERT_NEAR(expected_avg, realavg, 3.0);
}
TEST(to_rad_test, test)
{
	double x = helpers::TO_RAD * 0;
	ASSERT_NEAR(x, 0, 0.01);
	x = helpers::TO_RAD * 90;
	ASSERT_NEAR(x, helpers::MATH_PI / 2, 0.01);
	x = helpers::TO_RAD * 180;
	ASSERT_NEAR(x, helpers::MATH_PI, 0.01);
	x = helpers::TO_RAD * 270;
	ASSERT_NEAR(x, 3*helpers::MATH_PI/2, 0.01);
}
TEST(float_round_to_int, test)
{
	float x = 4.9f;
	int res = helpers::round_to_int(x);
	ASSERT(res == 5, "");

	x = 5.1f;
	res = helpers::round_to_int(x);
	ASSERT(res == 5, "");

	x = 5.5f;
	res = helpers::round_to_int(x);
	ASSERT(res == 6, "");
}
TEST(double_round_to_int, test)
{
	double x = 4.9;
	int res = helpers::round_to_int(x);
	ASSERT(res == 5, "");

	x = 5.1;
	res = helpers::round_to_int(x);
	ASSERT(res == 5, "");

	x = 5.5;
	res = helpers::round_to_int(x);
	ASSERT(res == 6, "");
}
TEST(Vec2Int_get_squared_distance_between_positions, test)
{
	{
		Vector2DInt origin(0, 0);
		Vector2DInt pos(10, 10);
		double res = helpers::get_squared_distance_between_positions(origin, pos);
		int rs = helpers::round_to_int(res);
		ASSERT(rs = 200, "");
	}
	{
		Vector2DInt origin(0, 0);
		Vector2DInt pos(-10, -10);
		double res = helpers::get_squared_distance_between_positions(origin, pos);
		int rs = helpers::round_to_int(res);
		ASSERT(rs = 200, "");
	}
}
TEST(Vec2_get_squared_distance_between_positions, test)
{
	{
		Vector2D origin(0, 0);
		Vector2D pos(10, 10);
		double res = helpers::get_squared_distance_between_positions(origin, pos);
		int rs = helpers::round_to_int(res);
		ASSERT(rs = 200, "");
	}
	{
		Vector2D origin(0, 0);
		Vector2D pos(-10, -10);
		double res = helpers::get_squared_distance_between_positions(origin, pos);
		int rs = helpers::round_to_int(res);
		ASSERT(rs = 200, "");
	}
}
