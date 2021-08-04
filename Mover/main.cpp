#include "Engine.h"
#include "Mover.h"

#include <iostream>


int main() {
	Window* window = new Window("Mover", 1920, 1080);
	Game* mover = new Mover();
	const Window::Input* inputs = &(window->getInputs());
	Engine engine = Engine(window, mover);
	engine.run();
}