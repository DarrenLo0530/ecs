#pragma once
#include "System.h"
#include <bullet/btBulletDynamicsCommon.h>

class PhysicsSystem : public UpdateSystem {
private:
	std::unique_ptr<btDefaultCollisionConfiguration> physicsConfig;
	std::unique_ptr<btCollisionDispatcher> physicsDispatcher;
	std::unique_ptr<btBroadphaseInterface> physicsCache;
	std::unique_ptr<btSequentialImpulseConstraintSolver> physicsSolver;
	std::unique_ptr<btDiscreteDynamicsWorld> physicsWorld;
	std::unique_ptr<btAlignedObjectArray<btCollisionShape>> physicsShapes;
public:
	void init() override;
	void update() override;

};