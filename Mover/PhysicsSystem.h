#pragma once
#include "System.h"
#include <bullet/btBulletDynamicsCommon.h>

class PhysicsSystem : public UpdateSystem {
private:
	btDefaultCollisionConfiguration* collisionConfig;
	btCollisionDispatcher* collisionDispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;

	std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> colliders;
public:
	void init() override;
	void update() override;
	void addEntity(Entity entity) override;
	bool removeEntity(Entity entity) override;
};