#pragma once
#include "component.hpp"
#include "harvestercontroller_cmp.hpp"

class PlayerControllerCmp : public Component
{
public:
	PlayerControllerCmp();
	void update()override;
private:
	double m_speed;
};