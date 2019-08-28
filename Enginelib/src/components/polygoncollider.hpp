#pragma once
#include "../collider.hpp"
#include <vector>

class PointContainer : std::vector<Vector2D>
{

};

class Projection
{
public:
	Projection(double min, double max) :m_min(min), m_max(max) {}
	const double m_min;
	const double m_max;
	bool overlap(const Projection& other);
	bool contains(const Projection& other);
	
private:
};

class CircleCollider;
class PolygonCollider :public Collider
{
public:
	PolygonCollider(GameObject* owner) :Collider(owner){}

	/*-------------------------------------------------------
	@param init_points - each point of the polygon collider in local space.
	---------------------------------------------------------*/
	void initialize(const std::initializer_list<Vector2D>& init_points);
	bool collides_with(const PolygonCollider* other);
	bool collides_with(const CircleCollider* other);
	const std::vector<Vector2D>& get_points()const;
	std::vector<Vector2D> get_points_worldpos()const;
	Vector2D get_centre_point_worldpos();
	static bool is_convex_simple(const std::vector<Vector2D> & points);
protected:
	void register_collider()override;
	void unregister_collider()override;
	friend class PhysxEngine;

private:
	static void calculate_normals(
		const std::vector <Vector2D>& points, 
		std::vector<Vector2D>& normals);
	bool do_projections_overlap(const std::vector<Vector2D>& normals, const std::vector<Vector2D>& first_points, const std::vector<Vector2D>& other_points);
	static Projection project(const Vector2D& axis, const std::vector<Vector2D>& points);
	Vector2D calculate_centre_point();
	std::vector<Vector2D> points;
	Vector2D centre_point;
};
