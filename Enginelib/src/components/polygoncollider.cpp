#include "polygoncollider.hpp"
#include "circlecollider.hpp"
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

bool Projection::contains(const Projection& other)
{
	if (m_min < other.m_min)
	{
		if (m_max > other.m_max)
		{
			return true;
		}
	}
	return false;
}

void PolygonCollider::initialize(const std::initializer_list<Vector2D>& init_points)
{
	points = std::vector(init_points);
	centre_point = calculate_centre_point();
}

bool PolygonCollider::collides_with(const PolygonCollider* other)
{

	const std::vector<Vector2D> mypoints_offset = get_points_worldpos();
	const std::vector<Vector2D> otherpoints_offset = other->get_points_worldpos();

	std::vector<Vector2D> my_normals(mypoints_offset.size());
	calculate_normals(mypoints_offset, my_normals);
	if (do_projections_overlap(my_normals, mypoints_offset, otherpoints_offset) == false) 
	{
		return false;
	}

	std::vector<Vector2D> other_normals(otherpoints_offset.size());
	calculate_normals(otherpoints_offset, other_normals);
	if (do_projections_overlap(other_normals, otherpoints_offset, mypoints_offset) == false)
	{
		return false;
	}



 	return true;
}

bool PolygonCollider::collides_with(const CircleCollider* other)
{
	const std::vector<Vector2D> worldpoints = get_points_worldpos();
	for (auto point : worldpoints)
	{
		const Vector2D diff = point - other->position();
		const Vector2D diff_norm = diff.normalized();
		std::vector<Vector2D> normals({ diff_norm });
		Vector2D circlepos1 = normals[0]*other->radius() + other->position();
		Vector2D circlepos2 = other->position() - normals[0] * other->radius();
		std::vector<Vector2D> circlepoints({ circlepos1, circlepos2 });
		if (do_projections_overlap(normals, worldpoints, circlepoints) == false)
		{
			return false;
		}
	}
	return true;
}

bool PolygonCollider::do_projections_overlap(const std::vector<Vector2D>& normals, const std::vector<Vector2D>& first_points, const std::vector<Vector2D>& other_points)
{
	for (auto normal : normals)
	{
		Projection p1 = project(normal, first_points);
		Projection p2 = project(normal, other_points);
		
		bool is_overlap = p1.overlap(p2);
		if (!is_overlap)
		{
			return false;
		}
		else
		{
			/*if (p1.contains(p2) || p2.contains(p1))
			{
				return true;
			}*/
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

/* Assume argument 2, normals, is already initiated to same size as argument 1, points. */
void PolygonCollider::calculate_normals(
	const std::vector <Vector2D> & points, 
	std::vector<Vector2D> & normals)
{
	for (int i = 0; i < points.size(); i++)
	{
		const Vector2D firstPoint = points[i];
		Vector2D secondPoint;
		if (i < points.size()-1)
		{
			secondPoint = points[i+1];
		}
		else
		{
			secondPoint = points[0];
		}
		const Vector2D edge = firstPoint - secondPoint;
		const Vector2D normal = edge.perpendicular();
		const Vector2D norm_norm = normal.normalized();
		normals[i] = norm_norm;		
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

Vector2D PolygonCollider::calculate_centre_point()
{
	Vector2D sum;
	for(int i = 0; i < points.size(); ++i)
	{
		sum += points[i];
	}
	sum /= points.size();
	return sum;
}

Vector2D PolygonCollider::get_centre_point_worldpos()
{
	Vector2D pos(centre_point);
	pos += owner().transform().get_position();
	return pos;
}

bool PolygonCollider::is_convex_simple(const std::vector<Vector2D>& points)
{
	if (points.size() < 3) return false; //Then it's a line or a point.
	double sign = 0;
	for (int i = 0; i < points.size(); i++)
	{
		const Vector2D first_point = points[i];
		Vector2D second_point = points[(i < points.size() - 1) ? i + 1 : 0];
		Vector2D third_point = points[(i < points.size() - 2) ? i + 2 : 1];
		double dx1 = second_point.x - first_point.x;
		double dy1 = second_point.y - first_point.y;
		double dx2 = third_point.x - second_point.x;
		double dy2 = third_point.y - second_point.y;
		if (sign == 0)
		{
			sign = dx1 * dy2 - dy1 * dx2;
		}
		else
		{
			double product = dx1 * dy2 - dy1 * dx2;
			if (sign > 0 && product < 0)
			{
				return false;
			}
			else if (sign < 0 && product > 0)
			{
				return false;
			}
		}
	}
	return true;
}


void PolygonCollider::register_collider()
{
	PhysxEngine::register_polygoncollider(this);
}

void PolygonCollider::unregister_collider()
{
	PhysxEngine::unregister_polygoncollider(this);
}
