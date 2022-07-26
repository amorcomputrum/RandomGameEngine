#include <float.h>
#include <math.h>

#include "RGE/Physics/Engine.h"

#include "RGE/Physics/Body.h"

RGE::physics::Body::Body(){}

RGE::physics::Body::Body(RGE::Vector2d position, float restitution, int mass, RGE::physics::Shape* shape, std::string id, bool hasGravity){
	this->position    = new RGE::Vector2d(position.x, position.y);
	this->velocity    = new RGE::Vector2d(0.0, 0.0);
	this->restitution = restitution;
	this->mass        = mass;
	this->id          = id;
	this->hasGravity  = hasGravity;
	if(mass == 0){
		inv_mass = 0.0;
	}else{
		inv_mass = 1.0/mass;
	}
	this->shape = shape;
	force       = new RGE::Vector2d();
	gravitationalForce = new RGE::Vector2d();
	updateCollider();
}

RGE::physics::Body::Body(RGE::Vector2d position, RGE::Vector2d velocity, float restitution, int mass, RGE::physics::Shape* shape, std::string id, bool hasGravity){
	this->position    = new RGE::Vector2d(position.x, position.y);
	this->velocity    = new RGE::Vector2d(velocity.x, velocity.y);
	this->restitution = restitution;
	this->mass        = mass;
	this->id          = id;
	this->hasGravity  = hasGravity;
	if(mass == 0){
		inv_mass = 0.0;
	}else{
		inv_mass = 1.0/mass;
	}
	this->shape = shape;
	force       = new RGE::Vector2d();
	gravitationalForce = new RGE::Vector2d();
	updateCollider();
}

void RGE::physics::Body::Update(double deltaTime){
	if(hasGravity){
	*velocity += (*force + RGE::physics::Engine::GRAVITY) +inv_mass;
	}else{
		*velocity += *force * inv_mass;
	}
	*position += *velocity*deltaTime;
	updateCollider();
}

void RGE::physics::Body::setLayer(int layer){
	this->layer = layer;
}

void RGE::physics::Body::setFriction(float staticF, float dynamicF){
	staticFriction = staticF;
	dynamicFriction = dynamicF;
}

void RGE::physics::Body::applyForce(RGE::Vector2d force){
	*this->force += force;
}

void RGE::physics::Body::applyForce(int x, int y){
	*this->force += RGE::Vector2d(x, y);
}

void RGE::physics::Body::applyImpulse(RGE::Vector2d impulse){
	*this->velocity += impulse;
}

void RGE::physics::Body::applyImpulse(int x, int y){
	*this->velocity += RGE::Vector2d(x, y);
}

void RGE::physics::Body::updateCollider(){
	switch(shape->id){
		case RGE::physics::Shape::ID::AABB:
			this->testCollider = RGE::physics::TestCollider(shape->w, shape->h, position->x, position->y);
			break;
		case RGE::physics::Shape::ID::Circle:
			this->testCollider = RGE::physics::TestCollider(shape->r*2.0, shape->r*2.0, (position->x-shape->r), (position->y-shape->r));
			break;
		case RGE::physics::Shape::ID::Line:
			this->testCollider = RGE::physics::TestCollider(shape->x2 - shape->x1, shape->y2 - shape->y1, position->x, position->y);
	}
}

void RGE::physics::Body::toggle(){
	enabled = !enabled;
}

void RGE::physics::Body::setState(bool enabled){
	this->enabled = enabled;
}

bool RGE::physics::Body::getEnabled(){
	return enabled;
}