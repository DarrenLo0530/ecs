#include "Entity.h"
#include "ComponentCoordinator.h"

class EntityHandle {
private:
	Entity id;
	std::shared_ptr<ComponentCoordinator> componentCoordinator;
public: 
	EntityHandle(Entity id, std::shared_ptr<ComponentCoordinator> componentCoordinator);

	template <typename ComponentType>
	void addComponent(ComponentType component);

	template <typename ComponentType>
	void removeComponent();

	template <typename ComponentType>
	void getComponent();

	Entity getId() const;
};