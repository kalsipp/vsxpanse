#include "polygoncollider.hpp"
#include "../graphicsmanager.hpp"
#include "../physxengine.hpp"


bool Projection::overlap(const Projection& other)
{
	if (m_min < other.m_min) 
	{
		return other.m_min - m_max < 0;
	}
	else 
	{
		return m_min - other.m_max < 0;
	}

}

void PolygonCollider::initialize(const std::initializer_list<Vector2D>& init_points)
{
	points = std::vector(init_points);
}

bool PolygonCollider::collides_with(const PolygonCollider* other)
{
	
	

	const Vector2D my_position = owner().transform().get_position();
	std::vector<Vector2D> mypoints_offset(points);
	helpers::add_to_all(mypoints_offset, my_position);
	
	const Vector2D other_position = other->owner().transform().get_position();
	std::vector<Vector2D> otherpoints_offset(other->get_points());
	helpers::add_to_all(mypoints_offset, other_position);

	std::vector<Vector2D> my_normals;
	calculate_normals(points, my_normals);
	for (auto normal : my_normals)
	{
		Projection p1 = project(normal, mypoints_offset);
		Projection p2 = project(normal, otherpoints_offset);
		if (p1.overlap(p2))
		{
			return true;
		}
	}


	std::vector<Vector2D> other_normals;
	calculate_normals(other->get_points(), other_normals);
	for (auto normal : other_normals)
	{
		
		Projection p1 = project(normal, mypoints_offset);
		Projection p2 = project(normal, otherpoints_offset);
		if (p1.overlap(p2))
		{
			return true;
		}
	}
	return false;
}

const std::vector<Vector2D>& PolygonCollider::get_points()const
{
	return points;
}

void PolygonCollider::calculate_normals(
	const std::vector <Vector2D> & points, 
	std::vector<Vector2D> & normals)
{
	normals.clear();
	for (int index = 0; index < points.size(); index++)
	{
		const Vector2D firstPoint = points[index];
		Vector2D secondPoint;
		if (index < points.size()-1)
		{
			secondPoint = points[index+1];
		}
		else
		{
			secondPoint = points[0];
		}
		const Vector2D edge = firstPoint - secondPoint;
		const Vector2D normal = edge.perpendicular();
		const Vector2D norm_norm = normal.normalized();
		normals.push_back(norm_norm);
	}
}

Projection PolygonCollider::project(const Vector2D& axis, const std::vector<Vector2D>& points)
{
	double min = axis.dot(points[0]);
	double max = min;
	for (int i = 1; i < points.size(); i++) 
	{
		double p = axis.dot(points[i]);
		if (p < min) 
		{
			min = p;
		}
		else if (p > max) 
		{
			max = p;
		}
	}
	Projection proj = Projection(min, max);
	return proj;
}

void PolygonCollider::register_collider()
{
	PhysxEngine::register_polygoncollider(this);
}

void PolygonCollider::unregister_collider()
{
	PhysxEngine::unregister_polygoncollider(this);
}
