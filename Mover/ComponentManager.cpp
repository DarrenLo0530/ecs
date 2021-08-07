#include "ComponentManager.h"

int ComponentIdCounter::counter = 0;

template <typename ComponentType>
void ComponentManager::addComponent(Entity entity, ComponentType component) {
	getComponentArray<ComponentType>()->addEntityComponent(entity, component);
}

template <typename ComponentType>
void ComponentManager::removeComponent(Entity entity) {
	getComponentArray<ComponentType>()->removeEntityComponent(entity);
}

template<typename ComponentType>
ComponentType& ComponentManager::getComponent(Entity entity) {
	return getComponentArray<ComponentType>()->getComponent(entity);
}

void ComponentManager::removeEntity(Entity entity) {
	for (auto const& pair : componentArrayMap) {
		auto const& componentArray = pair.second;
		componentArray->removeEntityComponent(entity);
	}
}
