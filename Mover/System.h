#pragma once
#include <set>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "EventManager.h"

class World;
class EntityHandle;

class BaseSystem {
protected:
	Signature signature;
	World* parentWorld = nullptr;

	std::set<EntityHandle> entities;
public:
	BaseSystem() = default;

	void addEntity(Entity entity);
	void removeEntity(Entity entity);
	const Signature& getSignature() const;

	void setParentWorld(World* world);

	template <typename ComponentType>
	void registerComponent() {
		signature.set(getComponentId<ComponentType>());
	}

	virtual void init() = 0;	
};

class UpdateSystem : public BaseSystem {
protected:
	std::shared_ptr<EventManager> eventManager = nullptr;
public:
	void setEventManager(std::shared_ptr<EventManager> eventManager);
	virtual void update() = 0;
};

class RenderSystem : public BaseSystem {
public:
	virtual void render() = 0;
};