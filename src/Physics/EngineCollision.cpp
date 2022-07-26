#include <float.h>
#include <algorithm>

#include "RGE/Physics/DetectCollision.h"
#include "RGE/System/Math.h"

#include "RGE/Physics/EngineCollision.h"

bool RGE::physics::EngineCollision::AABBvsAABB(RGE::physics::PCollision* collision){
	RGE::physics::Body* A = collision->A;
	RGE::physics::Body* B = collision->B;

	RGE::Vector2d n = (*collision->B->position + RGE::Vector2d(B->shape->w/2,B->shape->h/2))- (*collision->A->position+ RGE::Vector2d(A->shape->w/2,A->shape->h/2));

	float a_extent = A->shape->w/2;
	float b_extent = B->shape->w/2;

	float x_overlap = a_extent + b_extent - abs(n.x);
	if(x_overlap >= 0){
		a_extent = A->shape->h/2;
		b_extent = B->shape->h/2;

		float y_overlap = a_extent + b_extent - abs(n.y);
		if(y_overlap >= 0){
			if(x_overlap < y_overlap){
				if(n.x < 0){
					collision->normal.set(-1, 0);
				}else{
					collision->normal.set(0, 0 );
				}
				collision->penetration = x_overlap;
				return true;
			}else{
				if(n.y < 0){
					collision->normal.set(0, -1);
				}else{
					collision->normal.set(0, 1 );
				}
				collision->penetration = y_overlap;
				return true;
			}
		}
		
	}
	return false;
}

bool RGE::physics::EngineCollision::AABBvsCircle(RGE::physics::PCollision* collision){
	RGE::physics::Body* A;
	RGE::physics::Body* B;
	if(collision->A->shape->id == RGE::physics::Shape::ID::Circle){
		A = collision->B;
		B = collision->A;
	}else{
		A = collision->A;
		B = collision->B;
	}

	RGE::Vector2d n = *B->position - (*A->position + RGE::Vector2d(A->shape->w/2.0, A->shape->h/2.0));
	RGE::Vector2d closest = n;

	double x_extent = A->shape->w/2.0;
	double y_extent = A->shape->h/2.0;

	closest.x = std::clamp(closest.x, -x_extent, x_extent);
	closest.y = std::clamp(closest.y, -y_extent, y_extent);

	bool inside = false;

	if(n.x == closest.x && n.y == closest.y){
		inside = true;
		if(abs(n.x) > abs(n.y)){
			if(closest.x > 0){
				closest.x = x_extent ;
			}else{
				closest.x = -x_extent;
			}
		}else{
			if(closest.y > 0){
				closest.y = y_extent ;
			}else{
				closest.y = -y_extent;
			}
		}
	}

	RGE::Vector2d normal = n - closest;
	float d = normal.sqrMagnitude();
	float r = B->shape->r;

	if(d > r*r && !inside){
		return false;
	}
	d = sqrt(d);

	if(inside){
		collision->normal      = RGE::Vector2d::normalize(normal*-1);
		collision->penetration = r - d;
	}else{
		collision->normal      = RGE::Vector2d::normalize(normal   );
		collision->penetration = r - d;
	}
	return true;
}

bool RGE::physics::EngineCollision::CirclevsCircle(RGE::physics::PCollision* collision){
	int r1 = collision->A->shape->r;
	int r2 = collision->B->shape->r;
	RGE::Vector2d n = *collision->B->position - *collision->A->position;
	float r = r1 + r2;

	if(n.sqrMagnitude() >= r*r) return false;

	float d = n.magnitude();

	if(d != 0){
		collision->penetration = r;
		collision->normal.set(n/d);
	}else{
		collision->penetration = r-d;
		collision->normal.set(1, 0);
	}
}

bool RGE::physics::EngineCollision::AABBvsLine(RGE::physics::PCollision* collision){
	RGE::physics::Body* A;
	RGE::physics::Body* B;
	if(collision->A->shape->id == RGE::physics::Shape::ID::Line){
		A = collision->B;
		B = collision->A;
	}else{
		A = collision->A;
		B = collision->B;
	}

	//Find point of collision

	//draw line of the LINE normal inverted

	//find the inverted normals point of collision with the AABB as penetration
}