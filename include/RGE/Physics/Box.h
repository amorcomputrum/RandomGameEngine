#pragma once

#include "RGE/Physics/Shape.h"

namespace RGE{
	namespace physics{
		class Box : public RGE::physics::Shape{
		public:
			Box(double w, double h);
		};
	}
}
