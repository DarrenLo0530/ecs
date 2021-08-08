#pragma once

#include <memory>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

class SystemManager {
private:
	std::unordered_map<const char*, std::shared_ptr<System>> systems;
public:
#include "SystemManager.h"

	template <typename SystemType>
	std::shared_ptr<SystemType> registerSystem() {
		const char* systemTypeName = typeid(SystemType).name();
		assert(systems.find(systemTypeName) == systems.end() && "System is already registred");

		auto system = std::make_shared<SystemType>();
		systems.insert({ systemTypeName, system });
		return system;
	}

	void removeEntity(Entity entity) {
		for (auto const& p : systems) {
			p.second->removeEntity(entity);
		}
	}

	void entitySignatureChange(Entity entity, Signature entitySignature) {
		for (auto const& p : systems) {
			auto const& system = p.second;

			if ((entitySignature & system->getSignature()) == system->getSignature()) {
				system->addEntity(entity);
			} else {
				system->removeEntity(entity);
			}

		}
	}
};


