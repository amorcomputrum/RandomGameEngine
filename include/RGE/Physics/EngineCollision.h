#pragma once

#include "RGE/Physics/PCollision.h"
#include "RGE/System/Vector2d.h"

namespace RGE{
	namespace physics{
		class EngineCollision{
		public:
			static bool AABBvsAABB(RGE::physics::PCollision* collision);
			static bool AABBvsCircle(RGE::physics::PCollision* collision);
			static bool CirclevsCircle(RGE::physics::PCollision* collision);
			static bool AABBvsLine(RGE::physics::PCollision* collision);
			static bool CirclevsLine(RGE::physics::PCollision* collision);
		};
	}
}
