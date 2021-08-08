#pragma once
#include <set>
#include "Entity.h"

class System {
protected:
	Signature signature;
	std::set<Entity> entities;
public:
	System(const Signature& signature);

	void addEntity(Entity entity);
	void removeEntity(Entity entity);
	const Signature& getSignature();

	virtual void update() = 0;
};

