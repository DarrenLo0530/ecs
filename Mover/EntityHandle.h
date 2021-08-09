#pragma once

#include "Entity.h"
#include "World.h"

class EntityHandle {
private:
	Entity id;
	World* parentWorld;
public: 
	EntityHandle() {
		id = NULL;
		parentWorld = NULL;
	}

	EntityHandle(Entity id, World* parentWorld) {
		this->id = id;
		this->parentWorld = parentWorld;
	}

	~EntityHandle() = default;

	template <typename ComponentType>
	void addComponent(ComponentType& component) {
		parentWorld->addComponent(id, component);
	}

	template <typename ComponentType>
	void removeComponent() {
		parentWorld->removeComponent<ComponentType>(id);
	}

	template <typename ComponentType>
	ComponentType& getComponent() {
		return parentWorld->getComponent<ComponentType>(id);
	}

	Entity getId() const {
		return id;
	}

};