#pragma once

#include <memory>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"


class Coordinator {
private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<SystemManager> systemManager;
public:
	Coordinator();
	Entity createEntity();
	void destroyEntity(Entity entity);

	template <typename ComponentType>
	void registerComponent();

	template <typename ComponentType>
	void addComponent(Entity entity, ComponentType component);

	template <typename ComponentType>
	void removeComponent(Entity entity);

	template <typename ComponentType>
	ComponentType& getComponent(Entity entity);

	template <typename ComponentType>
	ComponentId getComponentId();

	template <typename SystemType>
	void registerSystem();

	template <typename SystemType>
	void setSystemSignature(Signature signature);

};

