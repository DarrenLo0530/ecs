#include "SystemManager.h"

template <typename SystemType>
std::shared_ptr<SystemType> SystemManager::registerSystem() {
	const char* systemTypeName = typeid(SystemType).name();
	assert(systems.find(systemTypeName) == systems.end() && "System is already registred");

	auto system = std::make_shared<SystemType>();
	systems.insert({ systemTypeName, system });
	return system;
}

template <typename SystemType>
void SystemManager::setSignature(Signature signature) {
	const char* systemTypeName = typeid(SystemType).name();
	assert(systems.find(systemTypeName) != systems.end() && "System was not registered yet");

	systemSignatures[systemTypeName] = signature;
}

void SystemManager::destroyEntity(Entity entity) {
	for (auto const& p: systems) {
		p.second->removeEntity(entity);
	}
}

void SystemManager::entitySignatureChange(Entity entity, Signature entitySignature) {
	for (auto const& p : systemSignatures) {
		auto const& systemTypeName = p.first;
		auto const& systemSignature = p.second;
		auto const& system = systems[systemTypeName];

		if ((entitySignature & systemSignature) == systemSignature) {
			system->addEntity(entity);
		} else {
			system->removeEntity(entity);
		}
		
	}
}