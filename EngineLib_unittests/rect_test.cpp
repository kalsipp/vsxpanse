#include "pch.h"
#include "basics/rect.hpp"

TEST(Constructor_noargs, test)
{
	Rect rec;
	ASSERT_TRUE(rec.x == 0);
	ASSERT_TRUE(rec.y == 0);
	ASSERT_TRUE(rec.w == 0);
	ASSERT_TRUE(rec.h == 0);
}
TEST(Constructor_args, test)
{
	double valx = 10.5;
	double valy = 102.3;
	double valw = 1203.3;
	double valh = 2102.2;
	Rect rec(valx, valy, valw, valh);
	ASSERT_TRUE(rec.x == valx);
	ASSERT_TRUE(rec.y == valy);
	ASSERT_TRUE(rec.w == valw);
	ASSERT_TRUE(rec.h == valh);
}
TEST(get_sdl_rect_test, test)
{
	double valx = 10.5;
	double valy = 102.3;
	double valw = 1203.3;
	double valh = 2102.9;
	Rect rec(valx, valy, valw, valh);
	SDL_Rect sdlrect = rec.get_sdl_rect();
	ASSERT_TRUE(sdlrect.x == 11);
	ASSERT_TRUE(sdlrect.y == 102);
	ASSERT_TRUE(sdlrect.w == 1203);
	ASSERT_TRUE(sdlrect.h == 2103);
}
