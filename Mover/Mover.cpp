#include "Mover.h"
#include "EntityHandle.h"
#include "Camera.h"
#include "BasicRenderSystem.h"
#include "ModelLoader.h"

void Mover::init() {
	gameWorld = new World();

	camera = gameWorld->createEntity();
	Camera::createCamera(&camera);
	gameWorld->registerRenderSystem<BasicRenderSystem>(&camera, dimensions);

	EntityHandle backpack = gameWorld->createEntity();

	Transform t = Transform{};
	t.position = glm::vec3(0.0, 0.0, -1.0);
	backpack.addComponent(t);

	Model m = ModelLoader::loadModel("models/backpack/backpack.obj");
	backpack.addComponent(m);

}


void Mover::update() {
	gameWorld->update();
}

void Mover::render(float interpolation) {
	gameWorld->render();
}