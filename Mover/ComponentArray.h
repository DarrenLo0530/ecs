#pragma once

#include <cassert>
#include <unordered_map>

#include "Entity.h"
#include <iostream>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void removeEntityComponent(Entity entity) = 0;
};
	
template<typename ComponentType>
class ComponentArray : public IComponentArray {
private:
	int size;
	std::array<ComponentType*, MAX_ENTITIES> componentArray;
	std::unordered_map<Entity, int> entityToIndexMap;
	std::unordered_map<int, Entity> indexToEntityMap;
public:
	void addEntityComponent(Entity entity, ComponentType& component) {
		assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component already added");

		ComponentType* test = &component;

		int componentIndex = size;
		entityToIndexMap[entity] = componentIndex;
		indexToEntityMap[componentIndex] = entity;
		componentArray[componentIndex] = &component;

		size++;
	}

	void removeEntityComponent(Entity entity) override {
		if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
			int lastComponentIndex = size - 1;
			int removedComponentIndex = entityToIndexMap[entity];

			// Remove component associated with entity from array and update entity index
			Entity replacingEntity = indexToEntityMap[lastComponentIndex];
			std::swap(componentArray[lastComponentIndex], componentArray[removedComponentIndex]);
			indexToEntityMap[removedComponentIndex] = replacingEntity;
			entityToIndexMap[replacingEntity] = removedComponentIndex;

			// Remove removed component of removed entity from maps (Now located at lastComponentIndex)
			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(lastComponentIndex);

			size--;
		}
	}


	ComponentType& getComponent(Entity entity) {
		assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
		return *componentArray[entityToIndexMap[entity]];
	}
};
