#include "RGE/System/Vector2d.h"
#include <iostream>
#include <cmath>

RGE::Vector2d::Vector2d(){
	x=0;
	y=0;
}

RGE::Vector2d::Vector2d(double x, double y){
	this->x = x;
	this->y = y;
}

float RGE::Vector2d::magnitude(){
	return std::sqrt((x*x) + (y*y));
}

float RGE::Vector2d::sqrMagnitude(){
	return ((x*x) + (y*y));
}

void RGE::Vector2d::set(double x, double y){
	this->x = x;
	this->y = y;
}

void RGE::Vector2d::set(RGE::Vector2d vec){
	this->x = vec.x;
	this->y = vec.y;
}

double RGE::Vector2d::getX(){
	return x;
}

double RGE::Vector2d::getY(){
	return y;
}

RGE::Vector2d RGE::Vector2d::operator+(RGE::Vector2d param){
	return RGE::Vector2d(x + param.x, y + param.y);
}

RGE::Vector2d RGE::Vector2d::operator+(double param){
	return RGE::Vector2d(x + param  , y + param  );
}

RGE::Vector2d& RGE::Vector2d::operator+=(const RGE::Vector2d& param){
	set(x + param.x, y + param.y);
	return *this;
}

RGE::Vector2d& RGE::Vector2d::operator+=(const double& param){
	set(x + param  , y + param  );
	return *this;
}

RGE::Vector2d RGE::Vector2d::operator-(RGE::Vector2d param){
	return RGE::Vector2d(x - param.x, y - param.y);
}

RGE::Vector2d RGE::Vector2d::operator-(double param){
	return RGE::Vector2d(x - param  , y - param  );
}

RGE::Vector2d& RGE::Vector2d::operator-=(const RGE::Vector2d& param){
	set(x - param.x, y - param.y);
	return *this;
}

RGE::Vector2d& RGE::Vector2d::operator-=(const double& param){
	set(x - param  , y - param  );
	return *this;
}

RGE::Vector2d RGE::Vector2d::operator/(RGE::Vector2d param){
	return RGE::Vector2d(x/param.x, y/param.y);
}

RGE::Vector2d RGE::Vector2d::operator/(double param){
	return RGE::Vector2d(x/param  , y/param  );
}

RGE::Vector2d RGE::Vector2d::operator*(RGE::Vector2d param){
	return RGE::Vector2d(x*param.x, y*param.y);
}

RGE::Vector2d RGE::Vector2d::operator*(double param){
	return RGE::Vector2d(x*param  , y*param  );
}

RGE::Vector2d& RGE::Vector2d::operator*=(const RGE::Vector2d& param){
	set(x*param.x, y*param.y);
	return *this;
}

RGE::Vector2d& RGE::Vector2d::operator*=(const double& param){
	set(x*param  , y*param  );
	return *this;
}

float RGE::Vector2d::dot(RGE::Vector2d vec1,RGE::Vector2d vec2){
	return (vec1.x*vec2.x) + (vec2.y*vec1.y  );
}

float RGE::Vector2d::cross(RGE::Vector2d vec1,RGE::Vector2d vec2){
	return (vec1.x*vec2.y) - (vec1.y - vec2.x);
}

RGE::Vector2d RGE::Vector2d::cross(RGE::Vector2d vec,float s){
	return RGE::Vector2d(s*vec.y, -s*vec.x);
}

RGE::Vector2d RGE::Vector2d::normalize(RGE::Vector2d vec){
	return (vec*(1.0/vec.magnitude()));
}
