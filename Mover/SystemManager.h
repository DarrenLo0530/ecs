#pragma once

#include <memory>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

class SystemManager {
private:
	std::unordered_map<const char*, std::shared_ptr<UpdateSystem>> updateSystems;
	std::unordered_map<const char*, std::shared_ptr<RenderSystem>> renderSystems;
public:
	template <typename SystemType>
	std::shared_ptr<SystemType> registerUpdateSystem() {
		const char* systemTypeName = typeid(SystemType).name();
		assert(updateSystems.find(systemTypeName) == updateSystems.end() && "System is already registred");

		auto system = std::make_shared<SystemType>();
		updateSystems.insert({ systemTypeName, system });
		return system;
	}

	template <typename SystemType>
	std::shared_ptr<SystemType> registerRenderSystem() {
		const char* systemTypeName = typeid(SystemType).name();
		assert(renderSystems.find(systemTypeName) == renderSystems.end() && "System is already registred");

		auto system = std::make_shared<SystemType>();
		renderSystems.insert({ systemTypeName, system });
		return system;
	}

	void removeEntity(Entity entity) {
		for (auto const& p : updateSystems) {
			p.second->removeEntity(entity);
		}
		for (auto const& p : renderSystems) {
			p.second->removeEntity(entity);
		}
	}

	void entitySignatureChange(Entity entity, Signature entitySignature) {
		for (auto const& p : updateSystems) {
			auto const& system = p.second;

			if ((entitySignature & system->getSignature()) == system->getSignature()) {
				system->addEntity(entity);
			} else {
				system->removeEntity(entity);
			}
		}

		for (auto const& p : renderSystems) {
			auto const& system = p.second;

			if ((entitySignature & system->getSignature()) == system->getSignature()) {
				system->addEntity(entity);
			} else {
				system->removeEntity(entity);
			}
		}
	}

	void update() {
		for (auto const& p : updateSystems) {
			auto& system = p.second;
			system->update();
		}
	}

	void render() {
		for (auto const& p : renderSystems) {
			auto& system = p.second;
			system->render();
		}
	}
};


