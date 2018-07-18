#include "debugcomponent.hpp"
#include "../map/astar.hpp"
#include "inputmanager.hpp"
#include "engine.hpp"
#include "components/spritecomponent.hpp"
#include "filesystem/resourcearchive.hpp"

void DebugComponent::setup()
{
	arch = new ResourceArchive("Resources");
}
void DebugComponent::update()
{
	Vector2DInt mouse_pos = InputManager::get_mouse_position();
	mouse_pos = Vector2DInt(mouse_pos.x, mouse_pos.y);
	const Vector2DInt screen_centre((1024) / 2, (768) / 2);
	std::stack<Vector2DInt> posses;
	Astar::get_path(screen_centre, mouse_pos, posses);
	while (markers.size() < posses.size())
	{
		GameObject * marker = Engine::add_gameobject<GameObject>();
		ResourceFile * file = arch->get_item("Images\\player.png");
		marker->add_component<SpriteComponent>()->load_sprite_from_image(file);
		markers.push_back(marker);
	}
	int indx = 0;
	while (!posses.empty())
	{
		Vector2DInt pos = Vector2DInt(posses.top().x, posses.top().y);
		markers[indx]->enabled() = true;
		markers[indx]->transform().set_position(pos);
		posses.pop();
		indx++;
	}
	while (indx < markers.size())
	{
		markers[indx]->enabled() = false;
		indx++;
	}
}