#include "EntityManager.h"

EntityManager::EntityManager() {
	for (Entity e = 0; e < MAX_ENTITIES; e++) {
		availableEntities.push(e);
	}

	numAvailableEntities = 0;
}

Entity EntityManager::createEntity() {
	// Get next available entity from queue
	Entity entity = availableEntities.front();
	availableEntities.pop();


	numAvailableEntities++;

	return entity;
}

void EntityManager::destroyEntity(Entity entity) {
	// Make entity id available again
	availableEntities.push(entity);

	// Reset signature of entity
	entitySignatures[entity].reset();
	numAvailableEntities--;
}

void EntityManager::setSignature(Entity entity, Signature signature) {
	entitySignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity) const {
	return entitySignatures[entity];	
}