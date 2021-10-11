#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "Component.h"

#include "Transform.h"
#include "Converter.h"

struct EntityMotionState : btMotionState {
	Transform* transform;
	EntityMotionState(Transform* transform) {
		this->transform = transform;
	}

	void getWorldTransform(btTransform& worldTrans) const override {
		worldTrans.getOrigin().setX(transform->position.x);
		worldTrans.getOrigin().setY(transform->position.y);
		worldTrans.getOrigin().setZ(transform->position.z);
	}

	void setWorldTransform(const btTransform& worldTrans) override {
		transform->position = Converter::btVectoVec(worldTrans.getOrigin());
	}
};

struct RigidBody : public Component<RigidBody> {
	btRigidBody* bulletRigidBody;

	RigidBody(btRigidBody* bulletRigidBody) {
		this->bulletRigidBody = bulletRigidBody;
	}
};
