#include "Rotatorcontroller.hpp"
#include "graphicsmanager.hpp"
void Rotatorcontroller::setup()
{
	int x = GraphicsManager::get_screen_width() / 2;
	int y = GraphicsManager::get_screen_height() / 2;
	owner().transform().set_position(Vector2D(x,y));
	rotation = 0.2;
}

void Rotatorcontroller::update()
{
	owner().transform().rotate(rotation);
}
