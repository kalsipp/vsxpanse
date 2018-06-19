#pragma once
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include "../basics/vector2d.hpp"
#include "../basics/vector3d.hpp"
#include "../basics/helpers.hpp"


class GameObject;
class Transform {
public:
	Transform();
	void move(const Vector3D &);
	void set_position(const Vector3D &);
	void rotate(const Vector3D &);
	void set_rotation(const Vector3D &);
	void set_scale(const Vector3D &);
	Vector3D get_position()const;
	Vector3D get_rotation()const;
	Vector3D get_scale()const;
private:
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale;
};
