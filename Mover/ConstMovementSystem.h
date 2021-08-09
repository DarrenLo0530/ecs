#pragma once

#include "EntityHandle.h"
#include "System.h"
#include "Entity.h"
#include "Transform.h"

class ConstMovementSystem : public System {
public:
	ConstMovementSystem() : System() {
		// Initialize signature	
		registerComponent<Transform>();

	}

	void update() override {
		for (EntityHandle entity : getEntities()) {
			auto& t = entity.getComponent<Transform>();
			t.position.x += 3;
		}
	}
};