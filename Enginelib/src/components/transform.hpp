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
	
	bool & dynamic(bool value);

	/*------------------------------------
	Sets the position.
	--------------------------------------
	Returns:   void
	Parameter: const Vector2D & pos
	Parameter: bool clear_z. sets position z to 0 is true. position z is not changed otherwise.
	------------------------------------*/
	void set_position(const Vector2D & pos, bool clear_z);
	void rotate(double amount);
	void rotate_around(double amount, Vector2D pivot_point);
	void set_scale(const Vector3D &);
	Vector3D get_position()const;
	double get_rotation()const;
	Vector3D get_scale()const;
private:
	void increase_rotation(double amount);
	bool m_dynamic = true;
	Vector3D m_position = Vector3D(0,0,0);
	double m_rotation = 0; 
	Vector3D m_scale = Vector3D(1,1,1);
};
