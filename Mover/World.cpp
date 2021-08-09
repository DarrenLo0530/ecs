#include "World.h"
#include "EntityHandle.h"

World::World() {
	componentManager = std::make_shared<ComponentManager>();
	entityManager    = std::make_shared<EntityManager>();
	systemManager    = std::make_shared<SystemManager>();

}

//Entities now handle components
EntityHandle World::createEntity() {
	return EntityHandle(entityManager->createEntity(), this);
}

void World::destroyEntity(EntityHandle entity) {
	// Destroy all entity's components
	removeAllComponents(entity.getId());

	// Then destroy entity itself
	entityManager->destroyEntity(entity.getId());
}


void World::update() {
	systemManager->update();
}