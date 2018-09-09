#pragma once
#include <stack>
#include "component.hpp"
#include "../resourcemanager.hpp"
#include "basics/vector2dint.hpp"
#include "basics/timer.hpp"
#include "agent.hpp"

class HarvestGenericResource : public AgentOrder
{
public:
	bool execute(Agent* unit)override;
	bool can_i_do_this(Agent* unit)override;
private:
	void find_resource();
	ResourceCmp * m_target_resource = nullptr;
	Vector2DInt m_current_movement_target;
};


class Harvester : public Agent
{
public:
	Harvester(GameObject * owner):Agent(owner){
		m_preferences.push_back(new HarvestGenericResource());
	}
	~Harvester()
	{
		for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it)
		{
			delete *it;
		}
	}
protected:
	float get_update_delay() final override { return m_update_delay_ms; }
	const float m_update_delay_ms = 1000;
private:
};