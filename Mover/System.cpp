#include "System.h"
#include "EntityHandle.h"

#include <iostream>

void System::addEntity(Entity entity) {
	entities.insert(EntityHandle(entity, parentWorld));
}

void System::removeEntity(Entity entity) {
	entities.erase(EntityHandle(entity, NULL));
}

const Signature& System::getSignature() const {
	return signature;
}


void System::setParentWorld(World* parentWorld) {
	this->parentWorld = parentWorld;
}

void System::setEventManager(std::shared_ptr<EventManager> eventManager) {
	this->eventManager = eventManager;
}