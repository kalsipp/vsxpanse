#pragma once
#include "component.hpp"
#include "harvestercontroller_cmp.hpp"

class PlayerControllerCmp : public Component
{
public:
	PlayerControllerCmp(GameObject * owner) :Component(owner) {}
	void update()override;
private:
	double m_speed = 1;
};