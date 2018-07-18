#include "agent.hpp"
#include "../map/gridmap.hpp"


void Agent::setup() 
{ 
	GridMap::register_unit(&owner(), m_solid); 
}

bool Agent::move(const Vector2DInt & to)
{
	return GridMap::move_unit(&(owner()), to, m_solid);
}

void Agent::update()
{
	int64_t elpst_time = m_update_timer.get_elapsed_milliseconds();
	if (elpst_time < get_update_delay()) return;
	m_update_timer.start();

	if (m_current_order != nullptr)
	{
		bool done = m_current_order->execute(this);
		if (done)
		{
			m_current_order = nullptr;
		}
	}
	else
	{
		figure_out_what_to_do();
	}
}

void Agent::figure_out_what_to_do()
{
	for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it)
	{
		if ((*it)->can_i_do_this(this))
		{
			m_current_order = (*it);
			break;
		}
	}
}
