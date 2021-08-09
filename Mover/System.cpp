#include "World.h"
#include "System.h"
#include "EntityHandle.h"
#include <iostream>
void System::addEntity(Entity entity) {
	entities.insert(entity);
}

void System::removeEntity(Entity entity) {
	entities.erase(entity);
}

const Signature& System::getSignature() {
	return signature;
}

std::vector<EntityHandle> System::getEntities() {
	std::vector<EntityHandle> entityHandles;
	entityHandles.reserve(entities.size());

	for (auto& entity : entities) {
		entityHandles.push_back(EntityHandle(entity, parentWorld));
	}

	return entityHandles;
}

void System::setParentWorld(World* parentWorld) {
	this->parentWorld = parentWorld;
}