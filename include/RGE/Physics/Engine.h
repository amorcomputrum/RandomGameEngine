#pragma once

#include <vector>

#include "RGE/Physics/PCollision.h"

namespace RGE{
	namespace physics{
		class Engine{
		public:
			static RGE::Vector2d GRAVITY;
			static bool PERFORMANCE_MODE;
			static bool VERTICAL_FRICTION;
			static float CORRECTION_PERCENT;
			static float CORRECTION_ALLOWANCE;
			static int FRAMERATE;
			std::vector<RGE::physics::Body*> bodies;
			RGE::physics::PCollision collision;
			Engine(int frameRate);
			void add(RGE::physics::Body* body);
			RGE::physics::Body* getById(std::string id);
			void removeById(std::string id);
			void Update();
			void HandleCollision(RGE::physics::PCollision* collision);
			void Impulse(RGE::physics::PCollision* collision);
			void PositionalCorrection(RGE::physics::PCollision* collision);
		private:
			void checkCollision(RGE::physics::Body* current, RGE::physics::Body* looking);
		};
	}
}
