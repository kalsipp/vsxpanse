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
		/* If we still don't have any resource to gather, we're done */
		if (m_target_resource == nullptr) return DONE;
	}

	GridMapUser * gridcomponent = unit->gridcomponent();
	ASSERT(gridcomponent, "Gridcomponent is null");
	if (unit->owner().transform().get_position() == m_target_resource->owner().transform().get_position())
	{
		m_target_resource->gather();
	}
	else
	{
		/* We are not at the resource, move find a path to it and start moving towards it  */
		bool have_valid_path = true;
		if (gridcomponent->get_num_pathfinder_steps_left() == 0)
		{
			have_valid_path = gridcomponent->calculate_path(m_target_resource->owner().transform().get_position());
		}

		/* We are at the current step, start moving towards the next step */
		if (have_valid_path)
		{
			MOVEMENT_STATUS status= gridcomponent->move_to_next_pathfinder_step();
			if (status != SUCCESSFUL_MOVE)
			{
				gridcomponent->clear_pathfinder_path();
			}
		}

		/* There was something in the way, recalculate path next round */

	}

	/* We did something this update, so we're not done */
	return NOT_DONE;
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

