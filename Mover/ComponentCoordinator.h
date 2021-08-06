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
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<SystemManager> systemManager;
public:
	ComponentCoordinator(
		std::shared_ptr<EntityManager> entityManager,
		std::shared_ptr<ComponentManager> componentManager,
		std::shared_ptr<SystemManager> systemManager	
	);

	template <typename ComponentType>
	void addComponent(Entity entity, ComponentType component);

	template <typename ComponentType>
	void removeComponent(Entity entity);

	template <typename ComponentType>
	ComponentType& getComponent(Entity entity);
};

