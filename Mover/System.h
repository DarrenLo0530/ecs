#pragma once
#include <set>
#include "Entity.h"

class System {
protected:
	Signature signature;
	std::set<Entity> entities;
public:
	System(Signature& signature);

	void addEntity(Entity entity);
	void removeEntity(Entity entity);
	const Signature& getSignature();
};

