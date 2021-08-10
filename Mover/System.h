#pragma once
#include <set>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "EventManager.h"

class World;
class EntityHandle;

class System {
protected:
	Signature signature;
	World* parentWorld = nullptr;
	std::shared_ptr<EventManager> eventManager = nullptr;

	std::set<EntityHandle> entities;
public:
	System() = default;
	virtual ~System() = default;

	void addEntity(Entity entity);
	void removeEntity(Entity entity);
	const Signature& getSignature() const;

	void setParentWorld(World* world);
	void setEventManager(std::shared_ptr<EventManager> eventManager);

	template <typename ComponentType>
	void registerComponent() {
		signature.set(getComponentId<ComponentType>());
	}

	virtual void init() = 0;
	virtual void update() = 0;
	
};

