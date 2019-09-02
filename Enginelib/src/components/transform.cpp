#include "transform.hpp"
#include "../gameobject.hpp"

Transform::Transform(){}

void Transform::move(const Vector3D & movement) {
	m_position += movement;
}

void Transform::rotate(double rot) 
{
	increase_rotation(rot);
}
void Transform::rotate_around(double rot, Vector2D pivot_point)
{
	m_position.rotate_around(rot, pivot_point);
	increase_rotation(rot);
}

void Transform::set_position(const Vector3D & position)
{
	m_position = position;
}

bool & Transform::dynamic(bool value)
{
	return m_dynamic;
}

void Transform::set_position(const Vector2D & pos, bool clear_z)
{
	if (m_dynamic)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		if (clear_z) m_position.z = 0;
	}
}

Vector3D Transform::get_position() const {
	return m_position;
}

double Transform::get_rotation() const {
	return m_rotation;
}

Vector3D Transform::get_scale() const {
	return m_scale;
}

void Transform::set_scale(const Vector3D & scale) {
	m_scale = scale;
}

void Transform::increase_rotation(double amount)
{
	m_rotation += amount;
	m_rotation = fmod(m_rotation, 360);
}
