#pragma once

#include "EntityHandle.h"
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "TestEvent.h"

class ConstMovementSystem : public System {
public:
	void init() override {
		registerComponent<Transform>();
	}

	void update() override {
		for (EntityHandle entity : entities) {
			auto& t = entity.getComponent<Transform>();
			t.position.x += 3;
			eventManager->publish(new TestEvent(entity));
		}

	}

};