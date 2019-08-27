#include "pch.h"
#define private public
#include "components/polygoncollider.hpp"

TEST(collideswith, helo)
{
	GameObject owner1(0);
	PolygonCollider poly1(&owner1);
	poly1.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });
	
	GameObject owner2(1);
	PolygonCollider poly2(&owner2);
	poly2.initialize({ Vector2D(0,0), Vector2D(10, 10), Vector2D(20, 0) });

	bool collides = poly1.collides_with(&poly2);
	ASSERT_TRUE(collides);
}

TEST(collideswith, not)
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
}

TEST(collideswith, different_shapes)
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
}
