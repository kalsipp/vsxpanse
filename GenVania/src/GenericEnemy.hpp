#pragma once
#include "gameobject.hpp"
#include "filesystem/resourcearchive.hpp"

class GenericEnemy:public GameObject
{
public:
	GenericEnemy(GAMEOBJECT_ID id):GameObject(id){}
	void setup();
private:
};