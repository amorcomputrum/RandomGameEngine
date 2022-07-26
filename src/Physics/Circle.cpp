#include "RGE/Physics/Circle.h"

RGE::physics::Circle::Circle(double r){
	this->r  = r;
	this->id = RGE::physics::Shape::ID::Circle;
}