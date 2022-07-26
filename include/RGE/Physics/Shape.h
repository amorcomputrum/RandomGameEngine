#pragma once

#include "RGE/System/Vector2d.h"

namespace RGE{
	namespace physics{
		class Shape{
		public:
			enum ID{
				AABB,Circle,Line
			};
			ID id;
			float r;
			int w,h;
			int x1,y1,x2,y2;
		};
	}
}
