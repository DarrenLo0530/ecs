#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class EntityHandle;

class World {
private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<SystemManager> systemManager;
	std::shared_ptr<EventManager> eventManager;

public:
	World();

	//Entities now handle components
	EntityHandle createEntity();
	void destroyEntity(EntityHandle entity);

	// Systems
	template <typename SystemType>
	std::shared_ptr<SystemType> registerSystem() {
		auto system = systemManager->registerSystem<SystemType>();
		system->setParentWorld(this);
		system->setEventManager(eventManager);
		system->init();
		return system;
	}

	template <typename ComponentType>
	void addComponent(Entity entity, ComponentType& component) {
		componentManager->addComponent(entity, component);


		ComponentId componentId = getComponentId<ComponentType>();
		entityManager->setSignatureBit(entity, componentId, true);
		systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
	}

	template <typename ComponentType>
	ComponentType& getComponent(Entity entity) {
		return componentManager->getComponent<ComponentType>(entity);
	}

	template <typename ComponentType>
	void removeComponent(Entity entity) {
		componentManager->removeComponent<ComponentType>(entity);

		ComponentId componentId = getComponentId<ComponentType>();
		entityManager->setSignatureBit(entity, componentId, false);

		systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
	}

	void removeAllComponents(Entity entity) {
		// Do not destroy entity from entity manager since we only want to delete association with components
		componentManager->removeEntity(entity);
		systemManager->removeEntity(entity);
	}

	void update();
	void render() const;


};