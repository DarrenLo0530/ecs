#include "ComponentManager.h"

template<typename ComponentType>
void ComponentManager::RegisterComponent() {
	const char* componentTypeName = typeid(ComponentType).name();
	ComponentId componentId = nextComponentId++;

	componentIdMap[componentTypeName] = componentId;
}

template<typename ComponentType>
ComponentId ComponentManager::getComponentId() {
	const char* componentTypeName = typeid(ComponentType).name();
	return componentIdMap[componentTypeName];
}

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

void ComponentManager::destroyEntity(Entity entity) {
	for (auto const& pair : componentArrayMap) {
		auto const& componentArray = pair.second;
		componentArray->destroyEntity(entity);
	}
}
