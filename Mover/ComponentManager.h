#pragma once
#include "ComponentId.h"
#include "ComponentArray.h"
#include <memory>

class ComponentManager {
private:
	std::unordered_map<const char*, ComponentId> componentIdMap;
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrayMap;

	ComponentId nextComponentId = 0;

	template <typename ComponentType>
	std::shared_ptr<ComponentArray<ComponentType>> getComponentArray() {
		const char* typeName = typeid(ComponentType).name();

		return std::static_pointer_cast<ComponentArray<ComponentType>>(componentArrayMap[typeName]);
	}

public:
	template <typename ComponentType>
	void RegisterComponent();

	template <typename ComponentType>
	ComponentId getComponentId();

	template <typename ComponentType>
	void addComponent(Entity entity, ComponentType component);

	template <typename ComponentType>
	void removeComponent(Entity entity);

	template <typename ComponentType>
	ComponentType& getComponent(Entity entity);

	void destroyEntity(Entity entity);
};