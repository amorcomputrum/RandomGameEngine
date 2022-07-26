#pragma once

#include "RGE/System/Vector2d.h"

namespace RGE{
	namespace physics{
		class TestCollider{
		public:
			float w,h,x,y;
			TestCollider();
			TestCollider(float w, float h, float x, float y);
			static bool CheckCollision(RGE::physics::TestCollider* t1, RGE::physics::TestCollider* t2);
		};
	}
}
