#include "RGE/Physics/Engine.h"
#include "RGE/Physics/EngineCollision.h"
#include "RGE/System/Exception.h"
#include "RGE/System/Math.h"

RGE::Vector2d RGE::physics::Engine::GRAVITY      = RGE::Vector2d(0,9.81);
bool  RGE::physics::Engine::PERFORMANCE_MODE        = true ;
bool  RGE::physics::Engine::VERTICAL_FRICTION       = false;
float RGE::physics::Engine::CORRECTION_PERCENT      = 0.5  ;
float RGE::physics::Engine::CORRECTION_ALLOWANCE    = 0.00 ;
int   RGE::physics::Engine::FRAMERATE               = 0    ;

RGE::physics::Engine::Engine(int frameRate){
	RGE::physics::Engine::FRAMERATE = frameRate;
}

void RGE::physics::Engine::add(RGE::physics::Body* body){
	bodies.push_back(body);
}

RGE::physics::Body* RGE::physics::Engine::getById(std::string id){
	for(int i = 0; i < bodies.size(); i++){
		if(bodies[i]->id == id){
			return bodies[i];
		}
	}
	throw RGE::exception("RGE::Engine::getById - No Such ID: " + id);
}

void RGE::physics::Engine::removeById(std::string id){
	for(int i = 0; i < bodies.size(); i++){
		if(bodies[i]->id == id){
			bodies.erase(bodies.begin()+i);
		}
	}
	throw RGE::exception("RGE::Engine::getById - No Such ID: " + id);
}

void RGE::physics::Engine::Update(){
	float deltaTime = 1.0/RGE::physics::Engine::FRAMERATE;
	//Check if in Performance Mode
	if(!RGE::physics::Engine::PERFORMANCE_MODE){
		//Performance Mode is disabled
		//Update all bodies
		for(int a = 0; a < bodies.size(); a++){
			RGE::physics::Body* current = bodies[a];
			current->Update(deltaTime);
		}
		//check for colisions
		for(int a = 0; a < bodies.size(); a++){
			RGE::physics::Body* current = bodies[a];
			if(current->enabled){
				//Check Broadphase Collision with dublicate culling
				for(int b = a; b < bodies.size(); b++){
					if(a != b){
						RGE::physics::Body* looking = bodies[b];
						checkCollision(current,looking);
					}
				}
			}
			current->force->set(0, 0);
		}
	}else{
		//Performance Mode is enabled
		//Update and check for collsions
		for(int a = 0; a < bodies.size(); a++){
			RGE::physics::Body* current = bodies[a];
			current->Update(deltaTime);
			if(current->enabled){
				//Check Broadphase Collision
				for(int b = 0; b < bodies.size(); b++){
					if(a != b){
						RGE::physics::Body* looking = bodies[b];
						checkCollision(current,looking);
					}
				}
			}
			current->force->set(0, 0);
		}			
	}
}
void RGE::physics::Engine::checkCollision(RGE::physics::Body* current, RGE::physics::Body* looking){
	if(looking->enabled){
		if(current->layer == looking->layer && !(current->inv_mass == 0.0 && looking->inv_mass == 0.0)){
			if(RGE::physics::TestCollider::CheckCollision(&current->testCollider, &looking->testCollider)){
				//Possible Collision
				collision = RGE::physics::PCollision{current, looking};
				switch(current->shape->id){

					case RGE::physics::Shape::ID::AABB:
						switch(looking->shape->id){
							case RGE::physics::Shape::ID::AABB:
								//AABBvsAABB
								if(RGE::physics::EngineCollision::AABBvsAABB(&collision)){
									HandleCollision(&collision);
								}
								break;

							case RGE::physics::Shape::ID::Circle:
								//AABBvsCircle
								if(RGE::physics::EngineCollision::AABBvsCircle(&collision)){
									HandleCollision(&collision);
								}
								break;						}
						break;

					case RGE::physics::Shape::ID::Circle:
						switch(looking->shape->id){
								case RGE::physics::Shape::ID::AABB:
									//CirclevsAABB
									if(RGE::physics::EngineCollision::AABBvsCircle(&collision)){
										collision.normal *= -1;
										HandleCollision(&collision);
									}
									break;

								case RGE::physics::Shape::ID::Circle:
									//CirclevsCircle
									if(RGE::physics::EngineCollision::CirclevsCircle(&collision)){
										HandleCollision(&collision);
									}
									break;
							}
						break;
				}
			}
		}
	}
}
void RGE::physics::Engine::HandleCollision(RGE::physics::PCollision* collision){
	Impulse(collision);
	PositionalCorrection(collision);
}

void RGE::physics::Engine::Impulse(RGE::physics::PCollision* collision){
	RGE::physics::Body* A = collision->A;
	RGE::physics::Body* B = collision->B;
	RGE::Vector2d normal  = RGE::Vector2d((float)collision->normal.x,(float)collision->normal.y);
	float penetration = collision->penetration;

	if(std::isnan(normal.x)){
		normal.x = 0;
	}
	if(std::isnan(normal.y)){
		normal.y = 0;
	}

	RGE::Vector2d rv  = *B->velocity - *A->velocity;

	float velAlongNormal = RGE::Vector2d::dot(rv,normal);

	if(velAlongNormal > 0){
		return;
	}

	float e = std::max(A->restitution, B->restitution);

	float j = -(1.0 + e)*velAlongNormal;
	j /= A->inv_mass + B->inv_mass;
	RGE::Vector2d impulse = normal*j;
	float sum_mass = A->mass + B->mass;
	float ratio = A->mass / sum_mass;
	if(std::isnan(ratio)){
		ratio = 1.0;
	}
	if(A->inv_mass != 0){
		*A->velocity -= (impulse*A->inv_mass)*ratio;
	}
	ratio = B->mass / sum_mass;
	if(B->inv_mass != 0){
		*B->velocity += (impulse*B->inv_mass)*ratio;
	}

	//FRICTION
	rv = *B->velocity - *A->velocity;

	RGE::Vector2d tangent = rv - (normal * RGE::Vector2d::dot(rv,normal));
	tangent = RGE::Vector2d::normalize(tangent);

	float jt = RGE::Vector2d::dot(rv,tangent) *-1;
	jt /= A->inv_mass + B->inv_mass;

	float mu = sqrt(pow(A->staticFriction,2) + pow(B->staticFriction,2));

	RGE::Vector2d frictionImpulse;
	if(abs(jt) < j * mu){
		frictionImpulse = tangent*jt;
	}else{
		float dynamicFriction = sqrt(pow(A->dynamicFriction,2) + pow(B->dynamicFriction,2));
		frictionImpulse = tangent * -j * dynamicFriction;
	}
	if(!RGE::physics::Engine::VERTICAL_FRICTION){
		frictionImpulse.y = 0;
	}
	*A->velocity -= frictionImpulse * A->inv_mass;
	*B->velocity += frictionImpulse * B->inv_mass;
}


void RGE::physics::Engine::PositionalCorrection(RGE::physics::PCollision* collision){
	RGE::physics::Body* A = collision->A;
	RGE::physics::Body* B = collision->B;
	float penetration        = collision->penetration;
	RGE::Vector2d normal  = RGE::Vector2d((float)collision->normal.x, (float)collision->normal.y);

	if(std::isnan(normal.x)){
		normal.x = 0;
	}
	if(std::isnan(normal.y)){
		normal.y = 0;
	}

	RGE::Vector2d correction = (normal*(std::max(penetration - RGE::physics::Engine::CORRECTION_ALLOWANCE,0.0f)/(A->inv_mass + B->inv_mass)))*RGE::physics::Engine::CORRECTION_PERCENT;

	if(A->inv_mass != 0){
		*A->position -= correction*A->inv_mass;
	}
	if(B->inv_mass != 0){
		*B->position += correction*B->inv_mass;
	}
}
