#include "SystemManager.h"

template <typename SystemType>
std::shared_ptr<SystemType> SystemManager::registerSystem() {
	const char* systemTypeName = typeid(SystemType).name();
	assert(systems.find(systemTypeName) == systems.end() && "System is already registred");

	auto system = std::make_shared<SystemType>();
	systems.insert({ systemTypeName, system });
	return system;
}

void SystemManager::destroyEntity(Entity entity) {
	for (auto const& p: systems) {
		p.second->removeEntity(entity);
	}
}

void SystemManager::entitySignatureChange(Entity entity, Signature entitySignature) {
	for (auto const& p : systems) {
		auto const& system = p.second;

		if ((entitySignature & system->getSignature()) == system->getSignature()) {
			system->addEntity(entity);
		} else {
			system->removeEntity(entity);
		}
		
	}
}