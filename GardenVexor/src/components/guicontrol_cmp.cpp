#include "guicontrol_cmp.hpp"
#include "inputmanager.hpp"
#include "basics/vector2dint.hpp"
#include "../map/gridmap.hpp"
#include "resource_cmp.hpp"
void GuiControlCmp::update()
{
	//bool lmb_press = InputManager::get_mouse_down(SDL_BUTTON_LEFT);
	//if (!lmb_press)
	//{
	//	SDL_MouseButtonEvent evnt;
	//	bool success = InputManager::get_latest_mouse_event(SDL_BUTTON_LEFT, &evnt);
	//	ASSERT(success, "Should be populated if button down");
	//	Vector2DInt position(evnt.x, evnt.y);
	//	std::vector<GameObject*>* objs = GridMap::get_objects_at_position(position);
	//	for (int item = 0; item < objs->size(); ++item)
	//	{
	//		GameObject * obj = (*objs)[item];
	//		ResourceCmp * cmp = obj->get_component<ResourceCmp>();
	//		if (cmp != nullptr)
	//		{

	//			break;
	//		}

	//	}
	//}
}