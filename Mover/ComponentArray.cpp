#include "ComponentArray.h"

template<typename ComponentType>
void ComponentArray<ComponentType>::addEntityComponent(Entity entity, ComponentType component) {
	assert(entityToIndexMap.find(entity) = entityToIndexMap.end() && "Component already added");

	int componentIndex = size;
	entityToIndexMap[entity] = componentIndex;
	indexToEntityMap[componentIndex] = entity;

	componentArray[componentIndex] = component;	
}

template<typename ComponentType>
void ComponentArray<ComponentType>::removeEntityComponent(Entity entity) {
	if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
		int lastComponentIndex = size - 1;
		int removedComponentIndex = entityToIndexMap[entity];

		// Remove component associated with entity from array and update entity index
		Entity replacingEntity = indexToEntityMap[lastComponentIndex];
		swap(componentArray[lastComponentIndex], componentArray[removedComponentIndex]);
		indexToEntityMap[removedComponentIndex] = replacingEntity;
		entityToIndexMap[replacingEntity] = removedComponentIndex;

		// Remove removed component of removed entity from maps (Now located at lastComponentIndex)
		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(lastComponentIndex);

		size--;
	}
}

template<typename ComponentType>
ComponentType& ComponentArray<ComponentType>::getComponent(Entity entity) const {
	return componentArray[entityToIndexMap[entity]];
}
