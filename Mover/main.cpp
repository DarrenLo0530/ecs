#include <iostream>
#include "Engine.h"
#include "Mover.h"
#include "Component.h"

#include "World.h"
#include "Transform.h"
#include "ConstMovementSystem.h"
#include "EntityHandle.h"
#include "ListenerSystem.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main() {
	stbi_set_flip_vertically_on_load(true);
	Window window = Window("Mover", 1920, 1080);
	Mover mover = Mover();

	Engine engine = Engine(&window, &mover);
	
	engine.run();

}