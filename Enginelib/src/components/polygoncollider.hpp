#pragma once
#include "../collider.hpp"
#include <vector>

class Projection
{
public:
	Projection(double min, double max) :m_min(min), m_max(max) {}
	const double m_min;
	const double m_max;
	bool overlap(const Projection& other);
	
private:
};

class PolygonCollider :public Collider
{
public:
	PolygonCollider(GameObject* owner) :Collider(owner){}

	/*-------------------------------------------------------
	---------------------------------------------------------
	@param init_points - each point of the polygon collider in local space.
	---------------------------------------------------------*/
	void initialize(const std::initializer_list<Vector2D>& init_points);
	bool collides_with(const PolygonCollider* other);
	const std::vector<Vector2D>& get_points()const;
	std::vector<Vector2D> get_points_worldpos()const;
protected:
	void register_collider()override;
	void unregister_collider()override;
	friend class PhysxEngine;

private:
	static void calculate_normals(
		const std::vector <Vector2D>& points, 
		std::vector<Vector2D>& normals);
	static Projection project(const Vector2D& axis, const std::vector<Vector2D>& points);
	Vector2D get_centre_point();
	std::vector<Vector2D> points;
	Vector2D centre_point;
};
