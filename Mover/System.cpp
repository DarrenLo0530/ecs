#include "System.h"

System::System(const Signature& signature) {
	this->signature = signature;
}
void System::addEntity(Entity entity) {
	entities.insert(entity);
}

void System::removeEntity(Entity entity) {
	entities.erase(entity);
}

const Signature& System::getSignature() {
	return signature;
}