#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "basics/rect.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(Rect_test)
	{
	public:

		TEST_METHOD(Constructor_noargs)
		{
			Rect rec;
			Assert::IsTrue(rec.x == 0);
			Assert::IsTrue(rec.y == 0);
			Assert::IsTrue(rec.w == 0);
			Assert::IsTrue(rec.h == 0);
		}
		TEST_METHOD(Constructor_args)
		{
			double valx = 10.5;
			double valy = 102.3;
			double valw = 1203.3;
			double valh = 2102.2;
			Rect rec(valx, valy, valw, valh);
			Assert::IsTrue(rec.x == valx);
			Assert::IsTrue(rec.y == valy);
			Assert::IsTrue(rec.w == valw);
			Assert::IsTrue(rec.h == valh);
		}
		TEST_METHOD(get_sdl_rect_test)
		{
			double valx = 10.5;
			double valy = 102.3;
			double valw = 1203.3;
			double valh = 2102.9;
			Rect rec(valx, valy, valw, valh);
			SDL_Rect sdlrect = rec.get_sdl_rect();
			Assert::IsTrue(sdlrect.x == 11);
			Assert::IsTrue(sdlrect.y == 102);
			Assert::IsTrue(sdlrect.w == 1203);
			Assert::IsTrue(sdlrect.h == 2103);
		}


	};
}