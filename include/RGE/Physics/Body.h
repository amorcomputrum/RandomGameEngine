#pragma once

#include <string>

#include "RGE/Physics/Box.h"
#include "RGE/Physics/Circle.h"
#include "RGE/Physics/Shape.h"
#include "RGE/Physics/TestCollider.h"
#include "RGE/System/Vector2d.h"

namespace RGE{
	namespace physics{
		class Body{
		public:
			RGE::physics::Shape* shape;
			bool hasGravity;
			float restitution;
			int mass;
			int layer = 0;
			float inv_mass;
			float staticFriction  = 1;
			float dynamicFriction = 1;
			bool enabled = true;
			RGE::physics::TestCollider testCollider;
			RGE::Vector2d* position;
			RGE::Vector2d* velocity;
			RGE::Vector2d* force;
			RGE::Vector2d* gravitationalForce;
			std::string id;
			Body();
			Body(RGE::Vector2d position, float restitution, int mass, RGE::physics::Shape* shape, std::string id, bool hasGravity);
			Body(RGE::Vector2d position, RGE::Vector2d velocity, float restitution, int mass, RGE::physics::Shape* shape, std::string id, bool hasGravity);
			void Update(double deltaTime);
			void setLayer(int layer);
			void setFriction(float staticF, float dynamicF);
			void applyForce(RGE::Vector2d force);
			void applyForce(int x, int y);
			void applyImpulse(RGE::Vector2d impulse);
			void applyImpulse(int x, int y);
			void updateCollider();
			void toggle();
			void setState(bool enabled);
			bool getEnabled();
		private:
			
		};
	}
}
