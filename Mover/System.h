#pragma once
#include <set>

class World;
class EntityHandle;

class System {
protected:
	Signature signature;
	World* parentWorld = NULL;
private:
	std::set<Entity> entities;
public:
	System() = default;
	virtual ~System() = default;

	void addEntity(Entity entity);
	void removeEntity(Entity entity);
	const Signature& getSignature();

	void setParentWorld(World* world);

	std::vector<EntityHandle> getEntities();

	template <typename ComponentType>
	void registerComponent() {
		signature.set(getComponentId<ComponentType>());
	}

	virtual void update() = 0;
	
};

