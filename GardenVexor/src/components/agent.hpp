#pragma once
#include "component.hpp"
#include "gameobject.hpp"
#include "basics/timer.hpp"
#include "agentorder.hpp"
#include "gridmapuser.hpp"

class Agent : public Component
{
public:
	Agent(GameObject * owner) :Component(owner)
	{
		m_update_timer.start();
	}
	void setup()override;
	bool move(const Vector2DInt & to);
	void initialize() {}
	void update()final override;
	void figure_out_what_to_do();
	GridMapUser * gridcomponent(); 
protected:
	virtual float get_update_delay() { return m_update_delay_ms; }
	const float m_update_delay_ms = 0;
	Timer m_update_timer;
	AgentOrder * m_current_order;
	std::vector<AgentOrder*> m_preferences;
	GridMapUser * m_gridcomponent = nullptr;
};
