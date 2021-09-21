#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "Component.h"

struct RigidBody : public Component<RigidBody> {
	bool isDynamic;
	btRigidBody* bulletRigidBody;

	RigidBody(btCollisionShape* collider, float mass, bool isDynamic) {
		this->isDynamic = isDynamic;

		// Setting up transform
		btTransform transform;
		transform.setIdentity();


		// Setting up dynamics
		btVector3 localInertia(0, 0, 0);
		if (isDynamic) {
			collider->calculateLocalInertia(mass, localInertia);
		}

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(btScalar(mass), motionState, collider, localInertia);
		bulletRigidBody = new btRigidBody(rbInfo);
	}
};
