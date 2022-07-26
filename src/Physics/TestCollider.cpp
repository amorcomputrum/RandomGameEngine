#include <iostream>

#include "RGE/Physics/TestCollider.h"

RGE::physics::TestCollider::TestCollider(){}

RGE::physics::TestCollider::TestCollider(float w, float h, float x, float y){
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
}

bool RGE::physics::TestCollider::CheckCollision(RGE::physics::TestCollider* t1, RGE::physics::TestCollider* t2){
	float x1 = t1->x;
	float y1 = t1->y;
	float w1 = t1->w;
	float h1 = t1->h;
	
	float x2 = t2->x;
	float y2 = t2->y;
	float w2 = t2->w;
	float h2 = t2->h;

	return ((((x1 + w1 > x2) && x1 < x2) || ((x1 < x2 + w2) && (x1 + w1 > x2))) && (((y1 + h1 > y2) && y1 < y2) || ((y1 < y2 + h2) && (y1 + h1 > y2))));
}