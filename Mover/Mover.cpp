#include "Mover.h"
#include "EntityHandle.h"
#include "Camera.h"
#include "BasicRenderSystem.h"
#include "ModelLoader.h"
#include "PlayerInput.h"

#include "PlayerInputSystem.h"
#include "PhysicsSystem.h"

#include "Converter.h"
#include <iostream>;
void Mover::init() {
	gameWorld = new World();

	camera = gameWorld->createEntity();
	Camera::createCamera(&camera);
	camera.getComponent<CameraComponent>().viewport = dimensions;

	// Systems
	gameWorld->registerUpdateSystem<PlayerInputSystem>();
	gameWorld->registerUpdateSystem<PhysicsSystem>();
	gameWorld->registerRenderSystem<BasicRenderSystem>(&camera);

	{
		EntityHandle cube = gameWorld->createEntity();

		Transform t = Transform{};
		t.position = glm::vec3(0.0, 0.0, -1.0);
		cube.addComponent(t);

		Model m = ModelLoader::loadModel("models/cube/cube.obj");
		cube.addComponent(m);
	}

	{
		EntityHandle player = gameWorld->createEntity();


		player.addComponent<Transform>(Transform{});

		View view{};
		view.viewCamera = camera;
		player.addComponent<View>(view);

		PlayerInput playerInput{};
		playerInput.input = inputs;
		player.addComponent<PlayerInput>(playerInput);
	}
}


void Mover::update() {
	gameWorld->update();
}

void Mover::render(float interpolation) {
	gameWorld->render();
}