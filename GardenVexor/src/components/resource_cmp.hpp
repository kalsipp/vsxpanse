#pragma once
#include "component.hpp"
#include "basics/vector2dint.hpp"
#include "../resourcemanager.hpp"

class GameObject;
class ResourceCmp : public Component
{
public:
	ResourceCmp(GameObject * owner) :Component(owner) {}
	void initialize(Vector2DInt center, RESOURCE_TYPE type);
	void gather();
	void teardown()override;
	double get_distance_to_center()const;
	RESOURCE_TYPE get_resource_type()const;
private:
	double m_distance_to_center;
	RESOURCE_TYPE m_resource_type;
};