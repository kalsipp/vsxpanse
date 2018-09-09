#pragma once
#include "components/circlecollider.hpp"

class PhysxEngine
{
public:
	static void initialize();
	static void teardown();
	static void update();
	static void render(); /* draws the colliders, for debugging */
	static void register_circlecollider(CircleCollider * coll);
	static void unregister_circlecollider(CircleCollider * coll);
	//static void register_squarecollider(SquareCollider * coll);
private:
	PhysxEngine() {}
	static void clear_all_collisions();
	static bool m_initialized;
	static std::vector<CircleCollider *> m_circlecolliders;
	//static std::vector<SquareColliders *> m_squarecolliders;
};