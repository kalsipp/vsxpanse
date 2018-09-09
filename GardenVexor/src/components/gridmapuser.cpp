#include "gridmapuser.hpp"
#include "../map/astar.hpp"
#include "../map/gridmap.hpp"
#include "agent.hpp"

void GridMapUser::setup()
{
	m_agent = owner().get_component<Agent>();
	ASSERT(m_agent != nullptr, "Could not find agent on my GameObject");
	GridMap::register_unit(&owner(), solid());
}
bool GridMapUser::move_in_grid(const Vector2DInt & dst)
{
	ASSERT(m_agent != nullptr, "Could not find agent on my GameObject");
	return GridMap::move_unit(&owner(), dst, solid());
}

bool GridMapUser::calculate_path(const Vector2DInt & dst)
{
	clear_pathfinder_path();
	return Astar::get_path(owner().transform().get_position(), dst, m_pathfind_path);
}

bool GridMapUser::get_next_pathfinder_step(Vector2DInt & outp)
{
	if (m_pathfind_path.empty()) return false;
	outp = m_pathfind_path.top();
	return true;
}

MOVEMENT_STATUS GridMapUser::move_to_next_pathfinder_step()
{
	Vector2DInt nextpos;
	bool success = get_next_pathfinder_step(nextpos);
	if (!success) return NO_MOVE_PATH_DONE;

	success = move_in_grid(nextpos);
	if (success) return SUCCESSFUL_MOVE;
	
	return COULD_NOT_MOVE;
}

void GridMapUser::clear_pathfinder_path()
{
	while (!m_pathfind_path.empty())
	{
		m_pathfind_path.pop();
	}
}

size_t GridMapUser::get_num_pathfinder_steps_left()
{ 
	return m_pathfind_path.size();
}