#include "harvestercontroller_cmp.hpp"

bool HarvestGenericResource::execute(Unit* unit)
{
	if (m_target_resource == nullptr)
	{
		find_resource();
	}
	return false;
}

void HarvestGenericResource::find_resource()
{

}

bool HarvestGenericResource::can_i_do_this(Unit* unit)
{
	return true;
}

void Unit::update()
{
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

void Unit::figure_out_what_to_do()
{
	for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it)
	{
		if (it->can_i_do_this(this))
		{
			m_current_order = &(*it);
			break;
		}
	}
}

//void Unit::give_order(const UnitOrder & order)
//{
//	m_my_order = new UnitOrder(order);
//}