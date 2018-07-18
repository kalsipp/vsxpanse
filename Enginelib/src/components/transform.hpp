#pragma once
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include "../basics/vector2d.hpp"
#include "../basics/vector3d.hpp"
#include "../basics/helpers.hpp"
#include "../basics/vector2dint.hpp"

class GameObject;
class Transform {
public:
	Transform();
	void move(const Vector3D &);
	void set_position(const Vector3D &);
	
	/*------------------------------------
	Sets the position.	
	--------------------------------------
	Returns:   void
	Parameter: const Vector2DInt & pos
	Parameter: bool clear_z. sets position z to 0 is true. position z is not changed otherwise.
	------------------------------------*/
	void set_position(const Vector2DInt & pos, bool clear_z = true);

	/*------------------------------------
	Sets the position.
	--------------------------------------
	Returns:   void
	Parameter: const Vector2D & pos
	Parameter: bool clear_z. sets position z to 0 is true. position z is not changed otherwise.
	------------------------------------*/
	void set_position(const Vector2D & pos, bool clear_z = true);
	void rotate(const Vector3D &);
	void set_scale(const Vector3D &);
	Vector3D get_position()const;
	Vector3D get_rotation()const;
	Vector3D get_scale()const;
private:
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale;
};
