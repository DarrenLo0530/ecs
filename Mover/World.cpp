#include "World.h"

World::World() {
	componentManager = std::make_shared<ComponentManager>();
	entityManager = std::make_shared<EntityManager>();
	systemManager = std::make_shared<SystemManager>();

	componentCoordinator = std::make_shared<ComponentCoordinator>(
		ComponentCoordinator(componentManager, entityManager, systemManager)
	);
}

//Entities now handle components
EntityHandle World::createEntity() {
	return EntityHandle(entityManager->createEntity(), componentCoordinator);
}

void World::destroyEntity(EntityHandle entity) {
	// Destroy all entity's components
	componentCoordinator->removeAllComponents(entity.getId());

	// Then destroy entity itself
	entityManager->destroyEntity(entity.getId());
}

// Systems
template <typename SystemType>
std::shared_ptr<SystemType> World::registerSystem() {
	return systemManager->registerSystem<SystemType>();
}