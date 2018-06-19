#include "basicsquarecollider.hpp"

BasicSquareCollider::BasicSquareCollider(const Vector2D & size): m_size(size)
{}

void BasicSquareCollider::update() {
	for (auto coll = m_all_colliders.begin();
	        coll != m_all_colliders.end(); ++coll) {
		auto sh_coll = *coll;
		ASSERT(sh_coll, "Colliderptr is null");
		// if (!sh_coll > already_colliding(m_me)) {

		// }
	}
}

