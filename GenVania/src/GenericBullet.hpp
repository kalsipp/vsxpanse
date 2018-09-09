#pragma once
#include "gameobject.hpp"
#include "filesystem/resourcearchive.hpp"
#include "BulletComponent.hpp"
#include "components/spritecomponent.hpp"
#include "components/circlecollider.hpp"
class GenericBullet:public GameObject
{
public:
	GenericBullet(GAMEOBJECT_ID id);
	void setup();
private:
	SpriteComponent * m_spritecomponent;
	BulletComponent * m_bulletcomponent;
	CircleCollider * m_collider;
};