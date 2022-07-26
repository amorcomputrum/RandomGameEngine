#include "RGE/Physics/Box.h"

RGE::physics::Box::Box(double w, double h){
	this->w        = w;
	this->h        = h;
	this->id       = RGE::physics::Shape::ID::AABB;
}
