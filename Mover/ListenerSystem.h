#pragma once

#include "System.h"
#include "TestEvent.h"

class ListenerSystem : public UpdateSystem {
public:
	void init() override {
		eventManager->subscribe(this, &ListenerSystem::listenerEvent);
	}

	void update() override {}

	void listenerEvent(TestEvent* event) {
		std::cout << event->entityA.getComponent<Transform>().position.x << std::endl;
	}
};