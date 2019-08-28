#include "pch.h"
#define private public
#include "components/polygoncollider.hpp"
#include "components/circlecollider.hpp"

TEST(polygoncollider, collideswith_basic)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	poly1.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });
	
	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly1.collides_with(&poly2);
	ASSERT_TRUE(collides);
	collides = poly2.collides_with(&poly1);
	ASSERT_TRUE(collides);
}

TEST(polygoncollider, collideswith_not)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	owner1.transform().set_position(Vector3D(200, 200, 200));
	poly1.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly1.collides_with(&poly2);
	ASSERT_FALSE(collides);
	collides = poly2.collides_with(&poly1);
	ASSERT_FALSE(collides);
}

TEST(polygoncollider, collideswith_different_shapes)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	poly1.initialize(
		{ 
			Vector2D(0,0), 
			Vector2D(10,20), 
			Vector2D(40, 40),
			Vector2D(60, 20),
			Vector2D(70, 0),
			Vector2D(60, -10),
			Vector2D(40, -20),
			Vector2D(20, -10)
		});
	
	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly1.collides_with(&poly2);
	ASSERT_TRUE(collides);
	collides = poly2.collides_with(&poly1);
	ASSERT_TRUE(collides);
}

TEST(polygoncollider, collideswith_differentPos)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	owner1.transform().set_position(Vector3D(5, 0, 0));
	poly1.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly1.collides_with(&poly2);
	ASSERT_TRUE(collides);
	collides = poly2.collides_with(&poly1);
	ASSERT_TRUE(collides);
}

TEST(polygoncollider, collideswith_circle)
{
	GameObject owner1(0);
	CircleCollider circle1(&owner1);
	owner1.transform().set_position(Vector3D(5, 0, 0));
	circle1.initialize(10, Vector2D(0,0));

	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly2.collides_with(&circle1);
	ASSERT_TRUE(collides);
}

TEST(polygoncollider, polygon_collision_containment)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	owner1.transform().set_position(Vector3D(1, 0, 0));
	poly1.initialize({ Vector2D(0,0), Vector2D(2, 2), Vector2D(4, 0) });
	
	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(1,0), Vector2D(2, 1), Vector2D(3, 0) });

	bool collides = poly2.collides_with(&poly1);
	ASSERT_TRUE(collides);
	collides = poly1.collides_with(&poly2);
	ASSERT_TRUE(collides);
}

TEST(polygoncollider, special_case)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	poly1.initialize(
		{ 
			Vector2D(0,0), 
			Vector2D(10,20), 
			Vector2D(40, 40),
			Vector2D(60, 20),
			Vector2D(70, 0),
			Vector2D(60, -10),
			Vector2D(40, -20),
			Vector2D(20, -10),

		 }
		);
	owner1.transform().set_position(Vector3D(168, 158, 0));
	

	GameObject owner2(1);
	owner2.transform().rotate(199.61);
	owner2.transform().set_position(Vector3D(512, 384, 0));
	PolygonCollider poly2(&owner2);
	poly2.initialize(
		{
			Vector2D(-502, -20),
			Vector2D(502, -20),
			Vector2D(502, 20),
			Vector2D(-502, 20)
		}
	);
	
	bool collides = poly2.collides_with(&poly1);
	ASSERT_FALSE(collides);
	collides = poly1.collides_with(&poly2);
	ASSERT_FALSE(collides);

}

TEST(polygoncollider, is_convex_simple_basic)
{
	{
		std::vector<Vector2D> points({Vector2D(0,0), Vector2D(1, 1), Vector2D(2, 0)});
		bool convex = PolygonCollider::is_convex_simple(points);
		ASSERT_TRUE(convex);
	}
	{
		std::vector<Vector2D> points(
			{
				Vector2D(0, 0), 
				Vector2D(2, 2),
				Vector2D(3, 1), 
				Vector2D(4, 2),
				Vector2D(5, 0),
			}
		);
		bool convex = PolygonCollider::is_convex_simple(points);
		ASSERT_FALSE(convex);
	}

}