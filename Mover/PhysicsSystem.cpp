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
	//{
	//	btCollisionShape* groundShape = new btBoxShape(btVector3(50, 50, 50));
	//	colliders.push_back(groundShape);

	//	btTransform groundTransform;
	//	groundTransform.setIdentity();
	//	groundTransform.setOrigin(btVector3(0, -56, 0));

	//	btScalar mass(0.);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);

	//	btDefaultMotionState* motionState = new btDefaultMotionState(groundTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, groundShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);

	//	dynamicsWorld->addRigidBody(body);
	//}

	//{
	//	//create a dynamic rigidbody

	//	//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
	//	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	//	colliders.push_back(colShape);

	//	/// Create Dynamic Objects
	//	btTransform startTransform;
	//	startTransform.setIdentity();

	//	btScalar mass(1.f);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		colShape->calculateLocalInertia(mass, localInertia);

	//	startTransform.setOrigin(btVector3(2, 10, 0));

	//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);


	//	dynamicsWorld->addRigidBody(body);
	//}
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

	for (EntityHandle entity : entities) {
		Transform transform = entity.getComponent<Transform>();
		btTransform bulletTransform = entity.getComponent<RigidBody>().bulletRigidBody->getWorldTransform();
	}
}


