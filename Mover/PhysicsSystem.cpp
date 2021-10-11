#include "Converter.h"
#include "PhysicsSystem.h"
#include "Transform.h"
#include "EntityHandle.h"
#include "RigidBody.h"

void PhysicsSystem::init() {
	registerComponent<Transform>();
	registerComponent<RigidBody>();

	collisionConfig = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(collisionConfig);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(collisionDispatcher, overlappingPairCache, solver, collisionConfig);
	
	dynamicsWorld->setGravity(btVector3(0.0, -9.8, 0.0));
}


void PhysicsSystem::addEntity(Entity entity) {
	EntityHandle addedEntity = wrapHandle(entity);

	RigidBody rigidBody = addedEntity.getComponent<RigidBody>();

	dynamicsWorld->addRigidBody(rigidBody.bulletRigidBody);
	colliders.push_back(rigidBody.bulletRigidBody->getCollisionShape());

	BaseSystem::addEntity(entity);
}

bool PhysicsSystem::removeEntity(Entity entity) {
	if (!BaseSystem::removeEntity(entity)) {
		return false;
	}
	

	// Thee entity was actually removed from the system
	EntityHandle removedEntity = wrapHandle(entity);

	RigidBody rigidBody = removedEntity.getComponent<RigidBody>();
	dynamicsWorld->removeRigidBody(rigidBody.bulletRigidBody);
	colliders.remove(rigidBody.bulletRigidBody->getCollisionShape());

	return true;
}

void PhysicsSystem::update() {
	dynamicsWorld->stepSimulation(1.0f/30.0f, 10);
}


