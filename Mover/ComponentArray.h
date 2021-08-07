#pragma once

#include <unordered_map>

#include "Entity.h"

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void removeEntityComponent(Entity entity) = 0;
};

template<typename ComponentType>
class ComponentArray : IComponentArray {
private:
	int size;
	std::array<ComponentType, MAX_ENTITIES> componentArray;
	std::unordered_map<Entity, int> entityToIndexMap;
	std::unordered_map<int, Entity> indexToEntityMap;
public:
	void addEntityComponent(Entity entity, ComponentType component);
	void removeEntityComponent(Entity entity) override;
	ComponentType& getComponent(Entity entity) const;
};