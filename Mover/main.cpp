#include <iostream>
#include "Engine.h"
#include "Mover.h"
#include "Component.h"

#include "World.h"
#include "Transform.h"
#include "ConstMovementSystem.h"
#include "EntityHandle.h"
#include "ListenerSystem.h"

int main() {
	World* world = new World();

	world->registerSystem<ConstMovementSystem>();
	world->registerSystem<ListenerSystem>();

	Transform t = Transform();
	t.p = 0;
	t.position.x = 3;
	t.position.y = 2;
	t.position.z = -1;

	EntityHandle e = world->createEntity();
	e.addComponent(t);

	while (true) {
		world->update();
	}

}