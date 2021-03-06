#pragma once
#include "component.hpp"
#include "components/textcomponent.hpp"
#include "collider.hpp"
class PlayerController:public Component
{
public:
	PlayerController(GameObject * owner) :Component(owner) {}
	void setup()override;
	void update()override;
private:
	double m_speed;
	TextComponent * m_text_comp;
	Collider * m_collider;
};