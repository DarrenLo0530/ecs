#include "EntityHandle.h"

EntityHandle::EntityHandle(Entity id, std::shared_ptr<ComponentCoordinator> componentCoordinator) {
	this->id = id;
	this->componentCoordinator = componentCoordinator;
}

template <typename ComponentType>
void EntityHandle::addComponent(ComponentType component) {
	componentCoordinator->addComponent(id, component);
}

template <typename ComponentType>
void EntityHandle::removeComponent() {
	componentCoordinator->removeComponent<ComponentType>(id);
}

template <typename ComponentType>
void EntityHandle::getComponent() {
	componentCoordinator->getComponent<ComponentType>(id);
}

Entity EntityHandle::getId() const {
	return id;
}