#include "transform.hpp"
#include "../gameobject.hpp"

Transform::Transform():
m_scale(1,1,1)
{

}

void Transform::move(const Vector3D & movement) {
	m_position += movement;
}

void Transform::rotate(const Vector3D & rotation) {
	m_rotation += rotation;
}
void Transform::set_position(const Vector3D & position)
{
	m_position = position;
}


Vector3D Transform::get_position() const {
	return m_position;
}

Vector3D Transform::get_rotation() const {
	return m_rotation;
}

Vector3D Transform::get_scale() const {
	return m_scale;
}

void Transform::set_scale(const Vector3D & scale) {
	m_scale = scale;
}

