#include "Engine.h"
#include "Mover.h"
#include "Component.h"
#include <iostream>

#include "World.h"

class Transform : public Component<Transform> {
public:
	int x, y, z;
};


int main() {
	World* world = new World();

	Transform t = Transform();
	t.x = 3;
	t.y = 2;
	t.z = -1;

	EntityHandle e = world->createEntity();

}