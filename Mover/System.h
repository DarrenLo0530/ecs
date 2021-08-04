#pragma once
#include <set>
#include "Entity.h"

class System {
protected:
	std::set<Entity> entities;
public:
	void addEntity(Entity entity) {
		entities.insert(entity);
	}

	void removeEntity(Entity entity) {
		entities.erase(entity);
	}
};

