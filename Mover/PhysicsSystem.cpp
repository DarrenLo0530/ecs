#include "PhysicsSystm.h"
#include "Transform.h"

void PhysicsSystem::init() {
	registerComponent<Transform>();
}

void PhysicsSystem::update() {
	// Advance physics world by 1/30th of a second (fixed update)
	physicsWorld->stepSimulation(1.0f/30.0f, 10);
}

