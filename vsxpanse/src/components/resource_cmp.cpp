#include "resource_cmp.hpp"


void ResourceCmp::initialize(Vector2DInt center, RESOURCE_TYPE type)
{
	m_resource_type = type;
	m_distance_to_center = helpers::get_squared_distance_between_positions(center, m_owner->transform().get_position());
	ResourceManager::register_resource(this);
}

void ResourceCmp::teardown()
{
	ResourceManager::unregister_resource(this);
}

void ResourceCmp::gather()
{

}

double ResourceCmp::get_distance_to_center()const
{
	return m_distance_to_center;
}

RESOURCE_TYPE ResourceCmp::get_resource_type()const
{
	return m_resource_type;
}


