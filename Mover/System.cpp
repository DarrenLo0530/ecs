#include "System.h"
#include "EntityHandle.h"

#include <iostream>

void BaseSystem::addEntity(Entity entity) {
	entities.insert(EntityHandle(entity, parentWorld));
}

void BaseSystem::removeEntity(Entity entity) {
	entities.erase(EntityHandle(entity, NULL));
}

const Signature& BaseSystem::getSignature() const {
	return signature;
}


void BaseSystem::setParentWorld(World* parentWorld) {
	this->parentWorld = parentWorld;
}

void UpdateSystem::setEventManager(std::shared_ptr<EventManager> eventManager) {
	this->eventManager = eventManager;
}


