#pragma once
#include <cmath>
#include "vector2d.hpp"
#include "helpers.hpp"
class Vector2D;

class Vector3D {
public:
	Vector3D() {}
	Vector3D(double _x, double _y = 0, double _z = 0);
	Vector3D(const Vector2D &);
	Vector3D operator+(const Vector3D&)const;
	Vector3D & operator+=(const Vector3D &);
	Vector3D & operator+=(const Vector2D &);
	Vector3D & operator-=(const Vector3D &);
	Vector3D & operator-=(const Vector2D &);
	Vector3D & operator*=(const Vector3D &);
	void set(double _x, double _y, double _z);
	bool operator==(const Vector3D &)const;
	bool operator!=(const Vector3D & rot);

	/*Will rotate this vector around x,y,z axis rot degrees on the spot*/
	void rotate(const Vector3D &);

	/*Will rotate this position rot degrees around the origin*/
	void rotate_around(const Vector3D & rot, const Vector3D & origin);
	
	/*Will rotate this vector around the z-axis rot degrees on the spot*/
	void rotate_z(double degrees); 

	/*Will rotate this vector around the y-axis rot degrees on the spot*/
	void rotate_y(double degrees); 
	
	/*Will rotate this vector around the z-axis rot degrees on the spot*/
	void rotate_x(double degrees); 

	/*Note Public member variables due to laziness*/
	double x = 0;
	double y = 0;
	double z = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Vector3D &);
private:
};