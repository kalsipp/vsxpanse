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
	centre_point = get_centre_point();
}

bool PolygonCollider::collides_with(const PolygonCollider* other)
{

	const std::vector<Vector2D> mypoints_offset = get_points_worldpos();
	const std::vector<Vector2D> otherpoints_offset = other->get_points_worldpos();

	std::vector<Vector2D> my_normals(points.size());
	calculate_normals(points, my_normals);
	for (auto normal : my_normals)
	{
		Projection p1 = project(normal, mypoints_offset);
		Projection p2 = project(normal, otherpoints_offset);
		if (!p1.overlap(p2))
		{
			return false;
		}
	}


	std::vector<Vector2D> other_normals(other->get_points().size());
	calculate_normals(other->get_points(), other_normals);
	for (auto normal : other_normals)
	{
		
		Projection p1 = project(normal, mypoints_offset);
		Projection p2 = project(normal, otherpoints_offset);
		if (!p1.overlap(p2))
		{
			return false;
		}
	}
	return true;
}

const std::vector<Vector2D>& PolygonCollider::get_points()const
{
	return points;
}

std::vector<Vector2D> PolygonCollider::get_points_worldpos()const
{
	const Vector2D my_position = owner().transform().get_position();
	const double my_rot = owner().transform().get_rotation();
	std::vector<Vector2D> mypoints_offset(points);
	helpers::add_to_all(mypoints_offset, my_position);
	const Vector2D global_centre_point = centre_point + my_position;
	for(int i = 0; i < mypoints_offset.size(); i++)
	{
		mypoints_offset[i].rotate_around(my_rot, global_centre_point);
	}
	return mypoints_offset;
}

/* Assume argument 2, normals, is already initiated to same size as argument 1 points */
void PolygonCollider::calculate_normals(
	const std::vector <Vector2D> & points, 
	std::vector<Vector2D> & normals)
{
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
		normals[index] = norm_norm;
		
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

Vector2D PolygonCollider::get_centre_point()
{
	Vector2D sum;
	for(int i = 0; i < points.size(); ++i)
	{
		sum += points[i];
	}
	sum /= points.size();
	return sum;
}

void PolygonCollider::register_collider()
{
	PhysxEngine::register_polygoncollider(this);
}

void PolygonCollider::unregister_collider()
{
	PhysxEngine::unregister_polygoncollider(this);
}
