#pragma once
#include "component.hpp"
class Rotatorcontroller :
	public Component
{
public:
	Rotatorcontroller(GameObject* owner) :Component(owner) {}
	void setup()override;
	void update()override;
private:
	float rotation;
};

