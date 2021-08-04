#include "Engine.h"
#include "Mover.h"
#include "Component.h"
#include <iostream>

struct Health : public Component<Health> {
	int currentHealth;
};

struct Transform : public Component<Transform> {
	int x, y, z;
};

int main() {
	Window* window = new Window("Mover", 1920, 1080);
	Game* mover = new Mover();
	Health h{};
	std::cout << "Health family: " << h.family() << std::endl;
	std::cout << "Transform family: " << getComponentFamily<Transform>() << std::endl;
}