
#include "Rotator.hpp"
#include "Rotatorcontroller.hpp"
#include "graphicsmanager.hpp"
#include "components/polygoncollider.hpp"
Rotator::Rotator(GAMEOBJECT_ID id) :GameObject(id)
{
}

void Rotator::setup()
{
	m_name = "Player";
	add_component<Rotatorcontroller>();
	int ysize = 20;
	int xsize = GraphicsManager::get_screen_width() / 2 - 10;
	add_component<PolygonCollider>()->initialize(
		{
			Vector2D(-xsize,-ysize),
			Vector2D(xsize,-ysize),
			Vector2D(xsize,ysize),
			Vector2D(-xsize,ysize),
		});
}
