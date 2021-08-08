#pragma once

#include <memory>

#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"


/*
* Coordinates the addition and removal of components from an entity
* 
* EntityManager is responsible for updating the entity's signature
* ComponentManager is responsible for updating the entity's components
* SystemManager is responsible for updating the entity's recorded in each system
*/


class ComponentCoordinator {
private:
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<SystemManager> systemManager;
public:
	ComponentCoordinator(
		std::shared_ptr<ComponentManager> componentManager,
		std::shared_ptr<EntityManager> entityManager,
		std::shared_ptr<SystemManager> systemManager
	) {
		this->entityManager = entityManager;
		this->componentManager = componentManager;
		this->systemManager = systemManager;
	}


	template <typename ComponentType>
	void addComponent(Entity entity, const ComponentType& component) {
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
};

