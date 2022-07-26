#include "RGE/Physics/Line.h"

RGE::physics::Line::Line(int x, int y){
	this->x = x;
	this->y = y;
	this->id = RGE::physics::Shape::ID::Line;
}
