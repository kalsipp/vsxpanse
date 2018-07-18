#pragma once

class Agent;
class AgentOrder
{
public:
	/* Returns true when done */
	virtual bool execute(Agent* unit) { return true; }
	virtual bool can_i_do_this(Agent* unit) { return false; }
	/* Return to default state */
	virtual void reset() {}
protected:
	enum ORDER_DONE
	{
		NOT_DONE,
		DONE
	};
};
