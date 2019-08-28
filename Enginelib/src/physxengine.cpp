#include "physxengine.hpp"
#include "basics/helpers.hpp"
#include "graphicsmanager.hpp"

bool PhysxEngine::m_initialized = false;
std::vector<CircleCollider *> PhysxEngine::m_circlecolliders;
std::vector<PolygonCollider*> PhysxEngine::m_polygoncolliders;

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
				register_collision(first, second);
			}

		}
	}

	for (size_t poly_coll = 0; poly_coll < m_polygoncolliders.size(); ++poly_coll)
	{
		PolygonCollider* first = m_polygoncolliders[poly_coll];
		for (size_t other_coll = 0; other_coll < m_polygoncolliders.size(); ++other_coll)
		{
			if (other_coll <= poly_coll) continue;
			PolygonCollider* second = m_polygoncolliders[other_coll];
			if (first->collides_with(second))
			{
				register_collision(first, second);
			}
		}
		for (size_t circle_coll = 0; circle_coll < m_circlecolliders.size(); ++circle_coll)
		{
			CircleCollider* second = m_circlecolliders[circle_coll];

			if (first->collides_with(second))
			{
				register_collision(first, second);
			}
		}
	}
}

void PhysxEngine::register_collision(Collider * coll1, Collider * coll2)
{
	Collision first_bam;
	first_bam.m_other_collidee = coll1;
	coll2->notify_collision(first_bam);
	Collision second_bam;
	second_bam.m_other_collidee = coll2;
	coll1->notify_collision(second_bam);
}

void PhysxEngine::render()
{
	for (size_t circle_coll = 0; circle_coll < m_circlecolliders.size(); ++circle_coll)
	{
		const Vector2D pos = m_circlecolliders[circle_coll]->owner().transform().get_position();
		const double radius = m_circlecolliders[circle_coll]->radius();
		const int radius_int = helpers::round_to_int(radius);
		GraphicsManager::draw_circle(pos, radius_int);
		GraphicsManager::draw_point(pos);
	}

	for (size_t coll = 0; coll < m_polygoncolliders.size(); ++coll)
	{
		const std::vector<Vector2D> points = m_polygoncolliders[coll]->get_points_worldpos();
		for (int index = 0; index < points.size(); index++)
		{
			Vector2D first_point = points[index];
			Vector2D second_point;
			if (index < points.size()-1)
			{
				second_point = points[index+1];
			}
			else
			{
				second_point = points[0];
			}
			GraphicsManager::set_render_draw_color(0xff, 0xff, 0xff, 0xff);
			GraphicsManager::draw_line(first_point, second_point);
			GraphicsManager::set_render_draw_color(255, 0, 0, 0);
			GraphicsManager::draw_point(first_point);
			GraphicsManager::set_render_draw_color(0xff, 0xff, 0xff, 0xff);
		}
			GraphicsManager::set_render_draw_color(0, 255, 0, 0);
			GraphicsManager::draw_point(m_polygoncolliders[coll]->owner().transform().get_position());
			GraphicsManager::set_render_draw_color(0, 0, 255, 0);
			GraphicsManager::draw_point(m_polygoncolliders[coll]->get_centre_point_worldpos());
			GraphicsManager::set_render_draw_color(0xff, 0xff, 0xff, 0xff);
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

void PhysxEngine::register_polygoncollider(PolygonCollider* coll)
{
	m_polygoncolliders.push_back(coll);
}

void PhysxEngine::unregister_polygoncollider(PolygonCollider* coll)
{
	auto it = std::find(m_polygoncolliders.begin(), m_polygoncolliders.end(), coll);
	ASSERT(it != m_polygoncolliders.end(), "Trying to remove non-existing collider");
	m_polygoncolliders.erase(it);
}


void PhysxEngine::clear_all_collisions()
{
	for (size_t coll = 0; coll < m_circlecolliders.size(); ++coll)
	{
		m_circlecolliders[coll]->clear_collisions();
	}
	for (size_t coll = 0; coll < m_polygoncolliders.size(); ++coll)
	{
		m_polygoncolliders[coll]->clear_collisions();
	}

}

//void PhysxEngine::register_squarecollider(SquareCollider * coll)
//{
//}

