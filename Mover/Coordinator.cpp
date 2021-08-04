#include "Coordinator.h"


Coordinator::Coordinator() {
	componentManager = std::make_unique<ComponentManager>();
	entityManager = std::make_unique<EntityManager>();
	systemManager = std::make_unique<SystemManager>();
}

Entity Coordinator::createEntity() {
	return entityManager->createEntity();
};

void Coordinator::destroyEntity(Entity entity) {
	componentManager->destroyEntity(entity);
	entityManager->destroyEntity(entity);
	systemManager->destroyEntity(entity);
}

template <typename ComponentType>
void Coordinator::registerComponent() {
	componentManager->registerComponent<ComponentType>();
}

template <typename ComponentType>
void Coordinator::addComponent(Entity entity, ComponentType component) {
	componentManager->addComponent(entity, entity);
	
	ComponentId componentId = getComponentId<ComponentType>();
	entityManager->setSignatureBit(entity, componentId, true);

	systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
}

template <typename ComponentType>
void Coordinator::removeComponent(Entity entity) {
	componentManager->removeComponent<ComponentType>(entity);

	ComponentId componentId = getComponentId<ComponentType>();
	entityManager->setSignatureBit(entity, componentId, false);

	systemManager->entitySignatureChange(entity, entityManager->getSignature(entity));
}

template <typename ComponentType>
ComponentType& Coordinator::getComponent(Entity entity) {
	return componentManager->getComponent(entity);
}

template <typename ComponentType>
ComponentId Coordinator::getComponentId() {
	return componentManager->getComponentId<ComponentType>();
}

template <typename SystemType>
void Coordinator::registerSystem() {
	return systemManager->registerSystem<SystemType>();
}

template <typename SystemType>
void Coordinator::setSystemSignature(Signature systemSignature) {
	systemManager->setSignature(systemSignature);
}