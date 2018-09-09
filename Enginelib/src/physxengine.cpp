#include "physxengine.hpp"
#include "basics/helpers.hpp"
#include "graphicsmanager.hpp"

bool PhysxEngine::m_initialized = false;
std::vector<CircleCollider *> PhysxEngine::m_circlecolliders;


void PhysxEngine::initialize()
{
	ASSERT(!m_initialized, "Can't initialize twice");
	m_initialized = true;
}

void PhysxEngine::teardown()
{
	ASSERT(m_initialized, "You have to init before tearing down");
	m_initialized = false;
}

void PhysxEngine::update()
{
	clear_all_collisions();
	for (size_t circle_coll = 0; circle_coll < m_circlecolliders.size(); ++circle_coll)
	{
		for (size_t other_coll = 0; other_coll < m_circlecolliders.size(); ++other_coll)
		{
			/* the first circle_coll will have to check everyone else 
			   the second circle_coll will have to check everyone else except the first
			   so if circle_coll = 1, skip other_coll = 0
			   so if circle_coll = 2, skip other_coll = 0, 1
			*/
			if (other_coll <= circle_coll) continue;
			CircleCollider * first = m_circlecolliders[circle_coll];
			CircleCollider * second = m_circlecolliders[other_coll];
			if (first->collides_with(second))
			{
				Collision first_bam;
				first_bam.m_other_collidee = second;
				first->notify_collision(first_bam);
				Collision second_bam;
				second_bam.m_other_collidee = first;
				second->notify_collision(second_bam);
			}

		}
	}
}

void PhysxEngine::render()
{
	for (size_t circle_coll = 0; circle_coll < m_circlecolliders.size(); ++circle_coll)
	{
		const Vector2D pos = m_circlecolliders[circle_coll]->owner().transform().get_position();
		const double radius = m_circlecolliders[circle_coll]->radius();
		const int radius_int = helpers::round_to_int(radius);
		GraphicsManager::render_circle(pos, radius_int);
	}
}

void PhysxEngine::register_circlecollider(CircleCollider * coll)
{
	m_circlecolliders.push_back(coll);
}

void PhysxEngine::unregister_circlecollider(CircleCollider * coll)
{
	auto it = std::find(m_circlecolliders.begin(), m_circlecolliders.end(), coll);
	ASSERT(it != m_circlecolliders.end(), "Trying to remove non-existing collider");
	m_circlecolliders.erase(it);
}

void PhysxEngine::clear_all_collisions()
{
	for (size_t circle_coll = 0; circle_coll < m_circlecolliders.size(); ++circle_coll)
	{
		m_circlecolliders[circle_coll]->clear_collisions();
	}

}

//void PhysxEngine::register_squarecollider(SquareCollider * coll)
//{
//}

