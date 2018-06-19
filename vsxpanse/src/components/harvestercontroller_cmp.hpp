#pragma once
#include "component.hpp"
class Unit;
class UnitOrder
{
public:
	/* Returns true when done */
	virtual bool execute(Unit* unit) { return true; }
	virtual bool can_i_do_this(Unit* unit) { return false; }
	virtual void reset() {}
};

class HarvestGenericResource : public UnitOrder
{
public:
	bool execute(Unit* unit)override;
	bool can_i_do_this(Unit* unit)override;
private:
	void find_resource();
	GameObject * m_target_resource = nullptr;

};

class Unit : public Component
{
public:
	void initialize() {}
	virtual void update()override;
	void figure_out_what_to_do();
protected:
	UnitOrder * m_current_order;
	std::vector<UnitOrder> m_preferences;
};

class Harvester : public Unit
{
	std::vector<UnitOrder> m_preferences = { HarvestGenericResource() };
};