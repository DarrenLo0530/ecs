#pragma once

#include <memory>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

class SystemManager {
private:
	std::unordered_map<const char*, std::shared_ptr<System>> systems;
public:
	template <typename SystemType>
	std::shared_ptr<SystemType> registerSystem();

	void removeEntity(Entity entity);
	void entitySignatureChange(Entity entity, Signature entitySignature);
};


