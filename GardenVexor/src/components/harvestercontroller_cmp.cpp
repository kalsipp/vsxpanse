#include "harvestercontroller_cmp.hpp"
#include "resource_cmp.hpp"
#include "../map/astar.hpp"
#include "../map/gridmap.hpp"


bool HarvestGenericResource::execute(Agent* unit)
{
	/* If this unit has nothing to work with, try to find something */
	if (m_target_resource == nullptr)
	{
		find_resource();
	}

	if (m_target_resource != nullptr)
	{
		
		if (unit->owner().transform().get_position() == m_target_resource->owner().transform().get_position())
		{
			m_target_resource->gather();
		}
		else
		{
			/* We are not at the resource, move find a path to it and start moving towards it  */
			if (m_movement_stack.empty())
			{
				Astar::get_path(unit->owner().transform().get_position(),
					m_target_resource->owner().transform().get_position(),
					m_movement_stack);
			}

			if (unit->owner().transform().get_position() == m_current_movement_target)
			{
				if (!m_movement_stack.empty())
				{
					m_current_movement_target = m_movement_stack.top();
					m_movement_stack.pop();
				}
			}
			bool success = unit->move(m_current_movement_target);
			/* There was something in the way, recalculate path next round */
			if (!success)
			{
				while (!m_movement_stack.empty())
				{
					m_movement_stack.pop();
				}
			}

		}
		/* We did something this update, so we're not done */
		return NOT_DONE;
	}
	else
	{
		/* If we still don't have any resource to gather, we're done */
		return DONE;
	}
}

void HarvestGenericResource::find_resource()
{
	m_target_resource = ResourceManager::get_resource_closest_to_center(GENERIC);
}

bool HarvestGenericResource::can_i_do_this(Agent* unit)
{
	(void)unit;
	return ResourceManager::get_resource_closest_to_center(GENERIC) != nullptr;
}

