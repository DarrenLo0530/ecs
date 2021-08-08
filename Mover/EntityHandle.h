#include "Entity.h"
#include "ComponentCoordinator.h"

class EntityHandle {
private:
	Entity id;
	std::shared_ptr<ComponentCoordinator> componentCoordinator;
public: 
	EntityHandle(Entity id, std::shared_ptr<ComponentCoordinator> componentCoordinator) {
		this->id = id;
		this->componentCoordinator = componentCoordinator;
	}

	template <typename ComponentType>
	void addComponent(const ComponentType& component) {
		componentCoordinator->addComponent(id, component);
	}

	template <typename ComponentType>
	void removeComponent() {
		componentCoordinator->removeComponent<ComponentType>(id);
	}

	template <typename ComponentType>
	ComponentType& getComponent() {
		return componentCoordinator->getComponent<ComponentType>(id);
	}

	Entity getId() const {
		return id;
	}
};