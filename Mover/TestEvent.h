#pragma once
#include "Event.h"

#include "EntityHandle.h"

struct TestEvent : public Event {
public:
	EntityHandle entityA;
	TestEvent(EntityHandle& a) : entityA{ a } {}
};