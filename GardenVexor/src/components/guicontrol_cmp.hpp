#pragma once
#include "component.hpp"

class GuiControlCmp: public Component
{
public:
	GuiControlCmp(GameObject * owner):Component(owner){}
	void update()override;
};