#include "CppUnitTest.h"

#include "CppUnitTestAssert.h"
#include "basics/helpers.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(Helpers_test)
	{
	public:

		TEST_METHOD(random_int_limits)
		{	
			const int min = 1;
			const int max = 2;
			for (int i = 0; i < 100; ++i) {
				int res = helpers::random_int(min, max);
				Assert::IsTrue(res >= min);
				Assert::IsTrue(res <= max);
			}
		}
		TEST_METHOD(random_int_randomness)
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
			Assert::AreEqual(expected_avg, realavg, 2.0);
		}
		TEST_METHOD(random_int_negative)
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
			Assert::AreEqual(expected_avg, realavg, 5.0);
		}
		TEST_METHOD(random_int_both_negative)
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
			Assert::AreEqual(expected_avg, realavg, 3.0);
		}
		TEST_METHOD(to_rad_test)
		{
			double x = helpers::TO_RAD * 0;
			Assert::AreEqual(x, 0, 0.01);
			x = helpers::TO_RAD * 90;
			Assert::AreEqual(x, helpers::MATH_PI / 2, 0.01);
			x = helpers::TO_RAD * 180;
			Assert::AreEqual(x, helpers::MATH_PI, 0.01);
			x = helpers::TO_RAD * 270;
			Assert::AreEqual(x, 3*helpers::MATH_PI/2, 0.01);

		}
	};
}