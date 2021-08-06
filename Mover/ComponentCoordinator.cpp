#include "ComponentCoordinator.h"


ComponentCoordinator::ComponentCoordinator(
	std::shared_ptr<EntityManager> entityManager,
	std::shared_ptr<ComponentManager> componentManager,
	std::shared_ptr<SystemManager> systemManager
) {
	this->entityManager = entityManager;
	this->componentManager = componentManager;
	this->systemManager = systemManager;
}

template <typename ComponentType>
void ComponentCoordinator::addComponent(Entity entity, ComponentType component) {
	componentManager->addComponent(entity, entity);
	
	ComponentId componentId = getComponentId<ComponentType>();
	entityManager->setSignatureBit(entity, componentId, true);

	systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
}

template <typename ComponentType>
void ComponentCoordinator::removeComponent(Entity entity) {
	componentManager->removeComponent<ComponentType>(entity);

	ComponentId componentId = getComponentId<ComponentType>();
	entityManager->setSignatureBit(entity, componentId, false);

	systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
}

template <typename ComponentType>
ComponentType& ComponentCoordinator::getComponent(Entity entity) {
	return componentManager->getComponent(entity);
}
