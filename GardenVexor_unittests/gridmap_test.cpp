#include "CppUnitTest.h"
#include "basics/vector2dint.hpp"
#include "map/gridmap.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GardenVexor_unittests
{
	TEST_CLASS(GridMap_test)
	{
	public:

		TEST_METHOD(gridspace_to_pixelspace_test)
		{
			{
				Vector2DInt gridspace(0, 0);
				Vector2DInt pixelspace = GridMap::gridspace_to_pixelspace(gridspace);
				Vector2DInt expected(0, 0);
				Assert::IsTrue(pixelspace == expected);
			}
			{
				Vector2DInt gridspace(1, 1);
				Vector2DInt pixelspace = GridMap::gridspace_to_pixelspace(gridspace);
				Vector2DInt expected(32, 32);
				Assert::IsTrue(pixelspace == expected);
			}
			{
				Vector2DInt gridspace(2, 2);
				Vector2DInt pixelspace = GridMap::gridspace_to_pixelspace(gridspace);
				Vector2DInt expected(64, 64);
				Assert::IsTrue(pixelspace == expected);
			}
			{
				Vector2DInt gridspace(-1, -1);
				Vector2DInt pixelspace = GridMap::gridspace_to_pixelspace(gridspace);
				Vector2DInt expected(-32, -32);
				Assert::IsTrue(pixelspace == expected);
			}
			{
				Vector2DInt gridspace(-2, -2);
				Vector2DInt pixelspace = GridMap::gridspace_to_pixelspace(gridspace);
				Vector2DInt expected(-64, -64);
				Assert::IsTrue(pixelspace == expected);
			}
		}

		TEST_METHOD(pixelspace_to_gridspace_test)
		{
			{
				Vector2DInt pixelspace(2 * GRIDTILESIZE, GRIDTILESIZE);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(2, 1);
				Assert::IsTrue(gridspace == expected);
			}

			{
				Vector2DInt pixelspace(0, 0);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(0, 0);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(1, 1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(0, 0);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(GRIDTILESIZE - 1, GRIDTILESIZE - 1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(0, 0);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(GRIDTILESIZE, GRIDTILESIZE);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(1, 1);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(GRIDTILESIZE + 1, GRIDTILESIZE + 1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(1, 1);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(-1, -1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(-1, -1);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(-GRIDTILESIZE + 1, -GRIDTILESIZE + 1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(-1, -1);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(-GRIDTILESIZE, -GRIDTILESIZE);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(-1, -1);
				Assert::IsTrue(gridspace == expected);
			}
			{
				Vector2DInt pixelspace(-GRIDTILESIZE - 1, -GRIDTILESIZE - 1);
				Vector2DInt gridspace = GridMap::pixelspace_to_gridspace(pixelspace);
				Vector2DInt expected(-2, -2);
				Assert::IsTrue(gridspace == expected);
			}

		}
	};
}