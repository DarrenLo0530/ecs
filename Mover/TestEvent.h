#pragma once
#include "Event.h"

#include "EntityHandle.h"

struct TestEvent : public Event {
public:
	EntityHandle entityA;
	TestEvent(const EntityHandle& a) : entityA{ a } {}
};