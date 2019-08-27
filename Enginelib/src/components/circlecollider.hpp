#pragma once
#include "../collider.hpp"


class CircleCollider : public Collider
{
public:
	CircleCollider(GameObject*owner) :Collider(owner), m_radius(0), m_offset(0,0) {}
	void initialize(double radius, const Vector2D & offset);
	Vector2D position()const;
	constexpr
	double radius()const;
protected:
	bool collides_with(const CircleCollider* other);
	void register_collider()override;
	void unregister_collider()override;
	friend class PhysxEngine;
private:
	Vector2D m_offset;
	double m_radius;
};

