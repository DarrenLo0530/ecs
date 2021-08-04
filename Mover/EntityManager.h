#pragma once

#include <queue>
#include <array>

#include "Entity.h"

class EntityManager {
private:
	std::queue<Entity> availableEntities;
	std::array<Signature, MAX_ENTITIES> entitySignatures;
	unsigned int numAvailableEntities;
public:
	EntityManager();
	Entity createEntity();
	void destroyEntity(Entity entity);
	void setSignature(Entity entity, Signature signature);
	Signature getSignature(Entity entity) const;
};

