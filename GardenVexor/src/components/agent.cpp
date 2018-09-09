#include "agent.hpp"

void Agent::setup() 
{ 
	m_gridcomponent = owner().get_component<GridMapUser>();
}

bool Agent::move(const Vector2DInt & to)
{
	if (m_gridcomponent == nullptr) return false;
	return m_gridcomponent->move_in_grid(to);
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

GridMapUser * Agent::gridcomponent() { return m_gridcomponent; }