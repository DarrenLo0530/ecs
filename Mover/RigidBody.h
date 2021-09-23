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

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		bulletRigidBody = new btRigidBody(10.0f, motionState, collider);
	}
};
