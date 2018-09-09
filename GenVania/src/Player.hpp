#pragma once
#include "gameobject.hpp"
#include "filesystem/resourcearchive.hpp"
class Player:public GameObject
{
public:
	Player(GAMEOBJECT_ID id);
	void setup();
private:
};