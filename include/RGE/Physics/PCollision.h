#pragma once

#include "RGE/Physics/Body.h"

namespace RGE{
	namespace physics{
		struct PCollision{
			RGE::physics::Body* A;
			RGE::physics::Body* B;
			float penetration = 0;
			RGE::Vector2d normal = RGE::Vector2d();
		};
	}
}
