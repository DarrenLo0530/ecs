#include "ComponentCoordinator.h"
#include "EntityManager.h"
#include "EntityHandle.h"


class World {
private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
	std::shared_ptr<SystemManager> systemManager;

	// Wrapper to abstract addition and removal of components
	std::shared_ptr<ComponentCoordinator> coordinator;
public:
	World();

	//Entities now handle components
	EntityHandle createEntity();
	void deleteEntity(EntityHandle entity);

	// Systems
	template <typename SystemType>
	std::shared_ptr<SystemType> registerSystem();
};