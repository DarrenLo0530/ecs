#pragma once

#include <memory>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

class SystemManager {
private:
	std::unordered_map<const char*, std::shared_ptr<System>> systems;
	std::unordered_map<const char*, Signature> systemSignatures;
public:
	template <typename SystemType>
	std::shared_ptr<SystemType> registerSystem();

	template <typename SystemType>
	void setSignature(Signature signature);

	void destroyEntity(Entity entity);
	void entitySignatureChange(Entity entity, Signature signature);
};


